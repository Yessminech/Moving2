import numpy as np
import os
import matplotlib.pyplot as plt
from env import goal_achieved
import logging

logging.basicConfig(level=logging.INFO)

class PolicyEvaluator:

    def plot_rewards_over_batches(rewards):
        directory = os.path.dirname(os.path.abspath(__file__))
        plt.plot(rewards)
        plt.title('Rewards over Batches')
        plt.xlabel('Batch Number')
        plt.ylabel('Reward')
        plt.savefig(os.path.join(directory, 'rewards_over_batches.png'))
        plt.close()
    
    def plot_average_rewards_over_episodes(rewards, episodes):
        directory = os.path.dirname(os.path.abspath(__file__))
        avg_rewards = [sum(rewards[:i+1])/(i+1) for i in range(len(rewards))]
        plt.plot(avg_rewards)
        plt.title('Average Rewards over Episodes')
        plt.xlabel('Episode Number')
        plt.ylabel('Average Reward')
        plt.savefig(os.path.join(directory, 'average_rewards_over_episodes.png'))
        plt.close()
    
    def get_best_action(Q_table, current_state, previous_state):
        curr_col, curr_dist = current_state
        prev_col, prev_dist = previous_state
        best_action = np.argmax(Q_table[curr_col, curr_dist, :, prev_col, prev_dist])
        logging.info(
            f"Best action for current state {current_state} and previous state {previous_state} is: {best_action}"
        )
        return best_action

    def number_of_steps_from_start(Q_table, color_mapping, distance_mapping, start_color='white', start_distance='dis_0'):
        done = False
        steps = 0  
        sample_state = (
            color_mapping[start_color],
            distance_mapping[start_distance],
        )
        sample_prev_state = (
            color_mapping[start_color],
            distance_mapping[start_distance],
        )
        while not done:
            sample_state, sample_prev_state = PolicyEvaluator.get_best_action(Q_table, sample_state, sample_prev_state)
            done = goal_achieved(start_color, sample_state, sample_prev_state)
            steps += 1  
        return steps
    
    def plot_values_distribution(Q_table):
        directory = os.path.dirname(os.path.abspath(__file__))
        Q_values = Q_table.flatten()
        plt.figure(figsize=(10, 6))
        plt.hist(Q_values, bins=30, alpha=0.75, color='blue', edgecolor='black')
        plt.title('Distribution of Q-values')
        plt.xlabel('Q-value')
        plt.ylabel('Frequency')
        plt.grid(True)
        plt.savefig(os.path.join(directory, 'qtable_valuess_distribution.png'))
        plt.close()