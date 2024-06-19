import numpy as np
from typing import Tuple, List, Dict

# Define the obsevation space
COLORS = ["white", "yellow", "blue", "red", "black", "brown"]
Distances = ["dis_0", "dis_1", "dis_2", "dis_3", "dis_4"]  ##dis4 is better than dis0
# Define the action space
ACTIONS = ["forward", "backward", "right", "left", "stop"]


def get_actions() -> List[str]:
    return ACTIONS


def get_distances() -> List[str]:
    return Distances


def get_colors() -> List[str]:
    return COLORS


def goal_achieved(state) -> bool:
    return state == ("red", "dis_4")


# Define the reward  function

# Define weights for the reward function
kd = 1.0
kc = 10.0
kg = 100.0

# Define the helper functions
def get_distance_value(distance: str) -> int:
    distance_map = {
        "dis_0": 1,
        "dis_1": 2,
        "dis_2": 3,
        "dis_3": 4,
        "dis_4": 5,  ##dis4 is better than dis0
    }
    return distance_map.get(distance, 0)  # default to 0 if color not found


def determine_distance_transition(current_distance: str, next_distance: str) -> str:
    """Determine if the distance transition is better, worse, or the same."""
    prev_value = get_distance_value(current_distance)
    curr_value = get_color_value(next_distance)
    if curr_value > prev_value:
        return "better"  ##dis4 is better than dis0
    elif curr_value < prev_value:
        return "worse"
    else:
        return "none"


def get_color_value(color: str) -> int:
    color_map = {"white": 1, "yellow": 2, "blue": 3, "red": 4, "black": 5, "brown": -10}
    return color_map.get(color, 0)  # default to 0 if color not found


def determine_color_transition(current_color: str, next_color: str) -> str:
    """Determine if the color transition is better, worse, or the same."""
    prev_value = get_color_value(current_color)
    curr_value = get_color_value(next_color)
    if curr_value > prev_value:
        return "better"
    elif curr_value < prev_value:
        return "worse"
    else:
        return "none"


# Define the main reward function
def calculate_reward(
    current_color,
    current_distance,
    next_color,
    next_distance,
    goal_achieved: bool,
    kd=kd,
    kc=kc,
    kg=kg,
) -> float:
    # Calculate R_distance
    ## TODO change this to include the distance change
    distance_change = determine_distance_transition(current_distance, next_distance)
    color_transition = determine_color_transition(current_color, next_color)

    if distance_change == "better":
        R_distance = kd * get_distance_value(next_distance)
    elif distance_change == "worse":
        R_distance = -kd * get_distance_value(next_distance)
    else:
        R_distance = 0

    # Calculate R_color
    if color_transition == "better":
        R_color = kc * get_color_value(next_color)
    elif color_transition == "worse":
        R_color = -kc * get_color_value(next_color)
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


#     def reset(self) -> None:
#         # Initialize the state (example: starting position)
#         self.state = ('white', 'dis_0')  # Example initial state
#         self.current_color = 'brown'
#         self.next_color = 'white'
#         self.previous_distance = 'dis_0'
#         self.goal_achieved = False
#         self.reward = 0
#         self.done = False
