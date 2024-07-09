import numpy as np
import random
import os
import pandas as pd
import glob
import ast
import logging
from collections import deque
import data_processing
from tqdm import tqdm
import matplotlib.pyplot as plt

from env import get_colors, get_distances, get_actions
from policy_evaluator import PolicyEvaluator

color_mapping = {color: i for i, color in enumerate(get_colors())}
distance_mapping = {distance: i for i, distance in enumerate(get_distances())}
action_mapping = {action: i for i, action in enumerate(get_actions())}


class QLearningAgent:
    def __init__(
        self,
        color_mapping,
        distance_mapping,
        action_mapping,
        learning_rate=0.5,
        discount_factor=0.99,
        num_episodes=100,
        batch_size=32,
    ):
        self.color_mapping = color_mapping
        self.distance_mapping = distance_mapping
        self.action_mapping = action_mapping
        self.learning_rate = learning_rate
        self.discount_factor = discount_factor
        self.num_episodes = num_episodes
        self.batch_size = batch_size
        self.replay_buffer = deque(maxlen=10000)
        self.Q_table = self.initialize_Q_table()
        self.rewards = []

    def initialize_Q_table(self):
        num_colors = len(self.color_mapping)
        num_distances = len(self.distance_mapping)
        num_actions = len(self.action_mapping)
        Q_table = np.zeros(
            (num_colors, num_distances, num_actions, num_colors, num_distances)
        )  # observation state contains preivous and current states
        return Q_table

    def populate_replay_buffer(self, dataset):
        with open(dataset, "r") as file:
            for line in file:
                index, data = line.split(":")
                data = data.strip()  # remove leading/trailing whitespace
                data_tuple = ast.literal_eval(data)
                self.replay_buffer.append(data_tuple)

    def sample_batch(self):
        return data_processing.random_slice(
            self.replay_buffer, min(len(self.replay_buffer), self.batch_size)
        )

    def update_Q_table(self, batch):
        prev_state = batch[0][0]  # takes initial state as previous state
        for state, action, next_state, reward, goal in batch:
            prev_col, prev_dist = (
                self.color_mapping[prev_state[0]],
                self.distance_mapping[prev_state[1]],
            )
            curr_col, curr_dist = (
                self.color_mapping[state[0]],
                self.distance_mapping[state[1]],
            )
            next_col, next_dist = (
                self.color_mapping[next_state[0]],
                self.distance_mapping[next_state[1]],
            )
            action = self.action_mapping[action]
            best_next_action = np.argmax(
                self.Q_table[next_col, next_dist, :, curr_col, curr_dist]
            )
            td_target = (
                reward
                + self.discount_factor
                * self.Q_table[
                    next_col, next_dist, best_next_action, curr_col, curr_dist
                ]
            )
            td_error = (
                td_target
                - self.Q_table[curr_col, curr_dist, action, prev_col, prev_dist]
            )
            self.Q_table[curr_col, curr_dist, action, prev_col, prev_dist] += (
                self.learning_rate * td_error
            )
            prev_state = state
        self.rewards.append(reward)

    def train(self):
        for episode in tqdm(
            range(self.num_episodes),
            desc="Training progress",
            bar_format="{l_bar}{bar}| {n_fmt}/{total_fmt}",
        ):
            batch = self.sample_batch()
            self.update_Q_table(batch)
        PolicyEvaluator.plot_rewards_over_batches(self.rewards)
        PolicyEvaluator.plot_average_rewards_over_episodes(
            self.rewards, self.num_episodes
        )
        PolicyEvaluator.plot_values_distribution(self.Q_table)
        # print(PolicyEvaluator.number_of_steps_from_start(self.Q_table, color_mapping, distance_mapping))       )

    def export_Q_table(self):
        current_dir = os.path.dirname(os.path.realpath(__file__))
        Q_table_path = os.path.join(current_dir, "Q_table.npy")
        try:
            np.save(Q_table_path, self.Q_table)
            logging.info(f"Q_table successfully saved at {Q_table_path}")
        except Exception as e:
            logging.error(f"Failed to save Q_table at {Q_table_path}. Error: {e}")

    def get_Q_table(self):
        return self.Q_table

    def convert_q_table_to_csv(self, q_table_npy_path, csv_path):
        Q_table = np.load(q_table_npy_path)
        flattened_Q_table = Q_table.reshape(-1).astype(float)
        df = pd.DataFrame(flattened_Q_table)
        df.to_csv(csv_path, header=False, index=False)
        print(f"Q-table successfully converted to CSV and saved at {csv_path}")

    def convert_csv_to_txt(self, csv_file, txt_file):
        # if file is already in txt format, just copy it
        if csv_file.endswith(".txt"):
            with open(csv_file, "r") as csv_file:
                with open(txt_file, "w") as txt_file:
                    txt_file.write(csv_file.read())
                    return

        with open(csv_file, "r") as csv_file:
            with open(txt_file, "w") as txt_file:
                for i, line in enumerate(csv_file):
                    # get colums from csv line t add apostrophes accordingly
                    columns = line.split(",")
                    if columns[0] == "((lila":
                        columns[0] = "((lilas"
                    columns[0] = columns[0][0:2] + "'" + columns[0][2:] + "'"
                    if columns[1][len(columns[1]) - 6] == "t":
                        columns[1] = columns[1][:-6] + columns[1][-5:]
                    elif columns[1][len(columns[1]) - 4] == "t":
                        columns[1] = columns[1][:-4] + columns[1][-3:]
                    columns[1] = " '" + columns[1][1:-1] + "')"

                    if columns[2] == " Invalid":
                        columns[2] = " 'stop'"
                    else:
                        columns[2] = columns[2][0:1] + "'" + columns[2][1:] + "'"
                    if columns[3] == " (lila":
                        columns[3] = " (lilas"
                    columns[3] = columns[3][0:2] + "'" + columns[3][2:] + "'"

                    if columns[4][len(columns[4]) - 4] == "t":
                        columns[4] = columns[4][:-4] + columns[4][-3:]
                    if columns[4][len(columns[4]) - 6] == "t":
                        columns[4] = columns[4][:-6] + columns[4][-5:]
                    columns[4] = " '" + columns[4][1:-1] + "')"

                    # write line to txt file
                    txt_file.write(f"{i+1}: {','.join(columns)}")
    def visualize_Q_table(self):
        # Visualize Q_table as csv table
        # Scheme:
        #                        |    current state
        # previous state, action |    reward
        

        # Get all possible colours and distances
        colours = list(self.color_mapping.keys())
        distances = list(self.distance_mapping.keys())
        states = [(dist, col) for dist in distances for col in colours]
        actions = list(self.action_mapping.keys())
        states_actions = [(state, action) for state in states for action in actions]

        # Create a dataframe with the Q_table
        #df = pd.DataFrame(index=pd.MultiIndex.from_tuples(states_actions), columns=states)
        df = pd.DataFrame(index=pd.MultiIndex.from_tuples(states_actions, names=['Previous State', 'Action']),
                      columns=pd.MultiIndex.from_tuples(states, names=['Current Distance', 'Current Colour']))

        # Adjusted loop for setting values in the DataFrame
        for state_action in states_actions:
            prev_state, action = state_action
            prev_dist, prev_col = prev_state
            action_idx = self.action_mapping[action]
            prev_col_idx = self.color_mapping[prev_col]
            prev_dist_idx = self.distance_mapping[prev_dist]
            # No change needed in the extraction of indices from mappings
            for state in states:
                curr_dist, curr_col = state                
                # Access Q_table with integer indices as before
                curr_col_idx = self.color_mapping[curr_col]
                curr_dist_idx = self.distance_mapping[curr_dist]
                reward = self.Q_table[curr_col_idx, curr_dist_idx, action_idx, prev_col_idx, prev_dist_idx]
                # Adjusted indexing to match DataFrame structure
                # Ensure that the row index is a tuple of (state, action) and column index is state
                df.loc[(prev_state, action), state] = reward
        df = df.loc[~(df == 0).all(axis=1)]
        df = df.loc[:, ~(df == 0).all(axis=0)]
        df.to_csv("rl/main/Q_table_visual.csv")
        plt.figure(figsize=(20, 10))
        plt.imshow(df.astype(float), cmap="coolwarm", interpolation="nearest")
        plt.colorbar()
        plt.show()



        
        


## TODO - Add performance tests for different configurations(learning rate, batch size, num_episodes..)
if __name__ == "__main__":
    training_dataset = False
    logging.basicConfig(level=logging.INFO)
    agent = QLearningAgent(color_mapping, distance_mapping, action_mapping)
    
    agent.batch_size = 4500
    agent.learning_rate = 0.7
    # file_name = "hardware/code/libraries/buildhat++/examples/moving2_src/test/data0.csv"
    # file_name get all pathes of files of hardware/code/libraries/buildhat++/examples/moving2_src/test/
    file_paths = glob.glob(
        os.path.join(
            "hardware/code/libraries/buildhat++/examples/moving2_src/test/", f"*.csv"
        )
    )
    # file_name = ["rl/main/generated_dataset/fake_dataset.txt"]
    for file_name in file_paths:
        if "data9" in file_name or "data3" in file_name:
            continue
        print(file_name)
        agent.convert_csv_to_txt(
            file_name, "rl/main/generated_dataset/training_dataset.txt"
        )
        agent.replay_buffer = deque(maxlen=10000)
        agent.populate_replay_buffer("rl/main/generated_dataset/training_dataset.txt")
        agent.train()
    agent.export_Q_table()
    agent.convert_q_table_to_csv(
        "rl/main/Q_table.npy", "rl/main/Q_table.csv"
    )
    
    agent.visualize_Q_table()
# /home/yessmine/Studies/6Semester/Project/Moving2/rl/main/Q_table.csv
