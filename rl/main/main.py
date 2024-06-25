import numpy as np
import random
import os
import ast
import logging
from collections import deque

import data_processing
from env import get_colors, get_distances, get_actions
from tqdm import tqdm

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
        num_episodes=10000,
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

    def train(self):
        for episode in tqdm(
            range(self.num_episodes),
            desc="Training progress",
            bar_format="{l_bar}{bar}| {n_fmt}/{total_fmt}",
        ):
            batch = self.sample_batch()
            self.update_Q_table(batch)

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
    
    def convert_csv_to_txt(self, csv_file, txt_file):
        # csv line will look like: ((white, dist_4), forward , (white, dist_4), 0, False)
        # txt lines should look like: n: (('white', 'dist_4'), 'forward', ('white', 'dist_4'), 0, False), where n is line number starting from 1
        with open(csv_file, "r") as csv_file:
            with open(txt_file, "w") as txt_file:
                for i, line in enumerate(csv_file):
                    # get colums from csv line t add apostrophes accordingly
                    columns = line.split(",")
                    columns[0] = columns[0][0:2] + "'" + columns[0][2:] + "'"

                    if columns[1][len(columns[1]) - 4] == "t":
                        columns[1] = columns[1][:-4] + columns[1][-3:]
                    columns[1] = " '" + columns[1][1:-1] + "')"

                    columns[2] = columns[2][0:1] + "'" + columns[2][1:] + "'"

                    columns[3] = columns[3][0:2] + "'" + columns[3][2:] + "'"

                    if columns[4][len(columns[4]) - 4] == "t":
                        columns[4] = columns[4][:-4] + columns[4][-3:]
                    columns[4] = " '" + columns[4][1:-1] + "')"

                    # write line to txt file
                    txt_file.write(f"{i+1}: {','.join(columns)}")
    

## TODO Convert .csv dataset to .txt
## TODO - Add performance tests for different configurations(learning rate, batch size, num_episodes..)
if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    agent = QLearningAgent(color_mapping, distance_mapping, action_mapping)
    agent.batch_size = 4500
    agent.learning_rate = 0.7
    agent.convert_csv_to_txt("hardware/code/libraries/buildhat++/examples/moving2_src/test/data0.csv", "rl/main/generated_dataset/test_dataset.txt")
    agent.populate_replay_buffer("rl/main/generated_dataset/test_dataset.txt")
    agent.train()
    agent.export_Q_table()
