import logging
from collections import deque
from tqdm import tqdm
from main import QLearningAgent, color_mapping, distance_mapping, action_mapping
import os
import numpy as np
logging.basicConfig(level=logging.INFO)

def test(Q_table, sample_state, sample_action):
    q_value = Q_table[sample_state + (sample_action,)]
    logging.info(f"Q-value for state {sample_state} and action {sample_action}: {q_value}")

def import_Q_table():
    current_dir = os.path.dirname(os.path.realpath(__file__))
    Q_table_path = os.path.join(current_dir, 'Q_table.npy')
    try:
        Q_table = np.load(Q_table_path)
        logging.info(f"Q_table successfully loaded from {Q_table_path}")
        return Q_table
    except FileNotFoundError:
        logging.error(f"Q_table not found at {Q_table_path}")
        return None
    
## Example test
test_color = 'red'
test_distance = 'dis_4'
test_action = 'forward'

## Compute the Q-value for the sample state and action
Q_table = import_Q_table()
sample_state = (color_mapping[test_color], distance_mapping[test_distance])
sample_action = action_mapping[test_action]
test(Q_table,sample_state, sample_action)