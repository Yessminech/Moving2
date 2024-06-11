import random
import os
from env import calculate_reward, determine_color_transition

# Define weights for the reward function
kd = 1.0
kc = 10.0
kg = 100.0

colors = ['white', 'yellow', 'blue', 'red', 'black', 'brown']
distances = ['dis_0', 'dis_1', 'dis_2', 'dis_3', 'dis_4']
actions = ['forward', 'backward', 'right', 'left', 'stop']

# Function to generate a synthetic dataset
## (('yellow', 'dis_3'), 'right', ('blue', 'dis_0'), 13.0, False)
def generate_fake_dataset():
    dataset = []
    for start_color in colors:
        for start_distance in distances:
            for action in actions:
                for end_color in colors:
                    for end_distance in distances:
                        goal_achieved = random.choice([True, False])
                        distance_change = random.uniform(-10.0, 10.0)
                        color_transition = determine_color_transition(start_color, end_color)
                        reward = calculate_reward(distance_change, color_transition, goal_achieved, kd, kc, kg)
                        sample = ((start_color, start_distance), action, (end_color, end_distance), reward, goal_achieved)
                        dataset.append(sample)
    return dataset

# Export the dataset as text files
fake_dataset = generate_fake_dataset()
new_dir = 'synth_all_data'
os.makedirs(new_dir, exist_ok=True)
with open(os.path.join(new_dir, 'fake_all_dataset.txt'), 'w') as f:
    for i, sample in enumerate(fake_dataset, start=1):
        f.write(f"{i}: {sample}\n")