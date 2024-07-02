import logging
from collections import deque
from tqdm import tqdm
from main import QLearningAgent, color_mapping, distance_mapping, action_mapping
import os
import numpy as np
from env import goal_achieved

logging.basicConfig(level=logging.INFO)
import pandas as pd


def convert_q_table_to_csv(q_table_npy_path, csv_path):
    """
    Convert the Q-table from a .npy file to a CSV file.
    """
    Q_table = np.load(q_table_npy_path)
    flattened_Q_table = Q_table.reshape(-1).astype(float)
    df = pd.DataFrame(flattened_Q_table)
    df.to_csv(csv_path, header=False, index=False)
    print(f"Q-table successfully converted to CSV and saved at {csv_path}")


def get_best_action(Q_table, current_state, previous_state):
    curr_col, curr_dist = current_state
    prev_col, prev_dist = previous_state
    best_action = np.argmax(Q_table[curr_col, curr_dist, :, prev_col, prev_dist])
    logging.info(
        f"Best action for current state {current_state} and previous state {previous_state} is: {best_action}"
    )
    return best_action


def test_Qvalue(Q_table, sample_state, sample_action, sample_prev_state):
    q_value = Q_table[sample_state + (sample_action,) + sample_prev_state]
    logging.info(
        f"Q-value for state {sample_state} and action {sample_action}: {q_value}"
    )


def import_Q_table():
    current_dir = os.path.dirname(os.path.realpath(__file__))
    Q_table_path = os.path.join(current_dir, "Q_table.npy")
    try:
        Q_table = np.load(Q_table_path)
        logging.info(f"Q_table successfully loaded from {Q_table_path}")
        return Q_table
    except FileNotFoundError:
        logging.error(f"Q_table not found at {Q_table_path}")
        return None


# # Example test
# test_curr_color = "red"
# test_curr_distance = "dis_4"
# test_action = "forward"
# test_prev_color = "blue"
# test_prev_distance = "dis_3"

# # Compute the Q-value for the sample state and action
Q_table = import_Q_table()
# if Q_table is not None:
#     sample_state = (
#         color_mapping[test_curr_color],
#         distance_mapping[test_curr_distance],
#     )
#     sample_prev_state = (
#         color_mapping[test_prev_color],
#         distance_mapping[test_prev_distance],
#     )
#     sample_action = action_mapping[test_action]
#     test_Qvalue(Q_table, sample_state, sample_action, sample_prev_state)
#     get_best_action(Q_table, sample_state, sample_prev_state)
# else:
#     logging.error("Failed to load Q_table for testing.")
