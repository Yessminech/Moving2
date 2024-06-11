import numpy as np
from typing import Tuple, List, Dict
# Define motor speed constants
FULL_REVERSE = -1
STOP = 0
FULL_FORWARD = 1

# Define actions and their corresponding motor speeds
ACTIONS = {
    "forward": (FULL_FORWARD, FULL_FORWARD),
    "backward": (FULL_REVERSE, FULL_REVERSE),
    "right": (FULL_REVERSE, FULL_FORWARD),
    "left": (FULL_FORWARD, FULL_REVERSE),
    "stop": (STOP, STOP),
    "undefined_1": (STOP, FULL_FORWARD),
    "undefined_2": (FULL_FORWARD, STOP),
    "undefined_3": (STOP, FULL_REVERSE),
    "undefined_4": (FULL_REVERSE, STOP)
}

def get_action(action_name: str) -> Tuple[int, int]:
    return ACTIONS.get(action_name, (STOP, STOP))

# Define weights for the reward function
kd = 1.0
kc = 10.0
kg = 100.0

COLORS = ['white', 'yellow', 'blue', 'red', 'black', 'brown']

def get_color_value(color: str) -> int:
    color_map = {
        'white': 1,
        'yellow': 2,
        'blue': 3,
        'red': 4,
        'black': 5,
        'brown': -10
    }
    return color_map.get(color, 0)  # default to 0 if color not found

def get_actions_length() -> int:
    return len(ACTIONS)

def get_colors_length() -> int:
    return len(COLORS)

def determine_color_transition(previous_color: str, current_color: str) -> str:
    """Determine if the color transition is better, worse, or the same."""
    prev_value = get_color_value(previous_color)
    curr_value = get_color_value(current_color)
    if curr_value > prev_value:
        return 'better'
    elif curr_value < prev_value:
        return 'worse'
    else:
        return 'none'

def calculate_reward(distance_change: float, color_transition: str, goal_achieved: bool, kd: float, kc: float, kg: float) -> float:
    # Calculate R_distance
    if distance_change < 0:
        R_distance = kd * abs(distance_change)
    elif distance_change > 0:
        R_distance = -kd * abs(distance_change)
    else:
        R_distance = 0

    # Calculate R_color
    if color_transition == 'better':
        R_color = kc
    elif color_transition == 'worse':
        R_color = -kc
    else:
        R_color = 0

    # Calculate R_goal
    if goal_achieved:
        R_goal = kg
    else:
        R_goal = 0

    # Total reward
    R = R_distance + R_color + R_goal
    return R

class Walk:
    def __init__(self, dataset: List[Tuple[Tuple[str, str], str, Tuple[str, str], float, bool]]) -> None:
        self.dataset = dataset
        self.reset()

    def observe(self) -> Tuple[str, str]:
        """Returns current state as (color, distance)"""
        return self.state

    def _update_state(self, action: str) -> None:
        """Updates the state based on the action using the dataset."""
        for transition in self.dataset:
            current_state, current_action, next_state, reward, done = transition
            if self.state == current_state and action == current_action:
                self.state = next_state
                self.reward = reward
                self.done = done
                break

    def _get_reward(self) -> float:
        return self.reward

    def _is_over(self) -> bool:
        return self.done

    def act(self, action: str) -> Tuple[Tuple[str, str], float, bool]:
        """Given an action, update the state, get the rewards, check if it is over"""
        self._update_state(action)
        reward = self._get_reward()
        game_over = self._is_over()
        return self.observe(), reward, game_over

    def reset(self) -> None:
        # Initialize the state (example: starting position)
        self.state = ('white', 'dis_0')  # Example initial state
        self.previous_color = 'white'
        self.current_color = 'white'
        self.previous_distance = 'dis_0'
        self.goal_achieved = False
        self.reward = 0
        self.done = False
        
# Example dataset (replace with actual data)
# (state, action, next_state, reward, done)
## Todo: use generate_fake_dataset
example_dataset = [
    (('white', 'dis_0'), 'left', ('white', 'dis_1'), 1, False),
    (('white', 'dis_1'), 'forward', ('yellow', 'dis_2'), 10, False),
    (('yellow', 'dis_2'), 'forward', ('red', 'dis_2'), 20, True)
]

# Map actions to indices for Q-table
ACTION_INDICES = {action: idx for idx, action in enumerate(ACTIONS.keys())}
# Initialize Walk environment and Q-learning agent
walk = Walk(example_dataset)



#agent = QLearningAgent(actions=ACTION_INDICES)
# Initialize Q-table
# state_size = 
# action_size =  
# q_table = np.zeros((state_size, action_size))
# Hyperparameters
# learning_rate = 0.8
# discount_rate = 0.95
# Batch Q-Learning
# for state, action, reward, next_state in dataset:
#     best_next_action = np.argmax(q_table[next_state, :])
#     td_target = reward + discount_rate * q_table[next_state, best_next_action]
#     q_table[state, action] = q_table[state, action] * (1 - learning_rate) + learning_rate * td_target
# Print updated Q-table
# print("\n\nQ-table\n")
# print(q_table)