import random
import os
from env import calculate_reward, determine_color_transition, determine_distance_transition, get_colors, get_distances, get_actions, goal_achieved

colors = get_colors()
distances = get_distances()
actions =  get_actions()

# Function to generate a synthetic dataset
## Fromat: (('yellow', 'dis_3'), 'right', ('blue', 'dis_0'), 13.0, False)
def generate_fake_dataset():
    dataset = []
    for current_color in colors:
        for current_distance in distances:
            for action in actions:
                for next_color in colors:
                    for next_distance in distances:
                        done = goal_achieved((next_color, next_distance))
                        distance_change = determine_distance_transition(current_distance, next_distance)
                        color_transition = determine_color_transition(current_color, next_color)
                        reward = calculate_reward(current_color, current_distance, next_color, next_distance, done)
                        experience = ((current_color, current_distance), action, (next_color, next_distance), reward, done)
                        dataset.append(experience)
    return dataset

# Export the dataset as text files
fake_dataset = generate_fake_dataset()
new_dir = 'generated_dataset'
os.makedirs(new_dir, exist_ok=True)
with open(os.path.join(new_dir, 'fake_dataset.txt'), 'w') as f:
    for i, experience in enumerate(fake_dataset, start=1):
        f.write(f"{i}: {experience}\n")