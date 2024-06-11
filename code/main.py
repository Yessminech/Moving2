import numpy as np
import random
import os
import ast
import logging
from collections import deque
from env import get_colors, get_distances, get_actions
from tqdm import tqdm

color_mapping = {color: i for i, color in enumerate(get_colors())}
distance_mapping = {distance: i for i, distance in enumerate(get_distances())}
action_mapping = {action: i for i, action in enumerate(get_actions())}
    
class QLearningAgent:
    def __init__(self, color_mapping, distance_mapping, action_mapping, learning_rate=0.1, discount_factor=0.99, num_episodes=1000, batch_size=32):
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
        Q_table = np.zeros((num_colors, num_distances, num_actions))
        return Q_table

    def populate_replay_buffer(self, dataset):
        with open(dataset, 'r') as file:
            for line in file:
                index, data = line.split(':')
                data = data.strip()  # remove leading/trailing whitespace
                data_tuple = ast.literal_eval(data)
                self.replay_buffer.append(data_tuple)

    def sample_batch(self):
        return random.sample(self.replay_buffer, min(len(self.replay_buffer), self.batch_size))

    def update_Q_table(self, batch):
        for state, action, next_state, reward, goal in batch:
            curr_col, curr_dist = self.color_mapping[state[0]], self.distance_mapping[state[1]]
            next_col, next_dist = self.color_mapping[next_state[0]], self.distance_mapping[next_state[1]]
            action = self.action_mapping[action]
            best_next_action = np.argmax(self.Q_table[next_col , next_dist])
            td_target = reward + self.discount_factor * self.Q_table[curr_col, curr_dist, best_next_action]
            td_error = td_target - self.Q_table[next_col , next_dist, action]
            self.Q_table[curr_col, curr_dist, action] += self.learning_rate * td_error

    def train(self):
        for episode in tqdm(range(self.num_episodes), desc="Training progress", bar_format='{l_bar}{bar}| {n_fmt}/{total_fmt}'):
            batch = self.sample_batch()
            self.update_Q_table(batch)

    def export_Q_table(self):
        current_dir = os.path.dirname(os.path.realpath(__file__))
        Q_table_path = os.path.join(current_dir, 'Q_table.npy')
        try:
            np.save(Q_table_path, self.Q_table)
            logging.info(f"Q_table successfully saved at {Q_table_path}")
        except Exception as e:
            logging.error(f"Failed to save Q_table at {Q_table_path}. Error: {e}")

##TODO - Add performance tests for different configurations(learning rate, batch size, num_episodes..)
if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    agent = QLearningAgent(color_mapping, distance_mapping, action_mapping)
    agent.batch_size = 4500 
    agent.learning_rate = 0.7
    agent.populate_replay_buffer('generated_dataset/fake_dataset.txt')
    agent.train()
    agent.export_Q_table()