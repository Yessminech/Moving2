import random
import os
from env import calculate_reward, determine_color_transition

# Define weights for the reward function
kd = 1.0
kc = 10.0
kg = 100.0

colors = ["white", "yellow", "blue", "red", "black", "brown"]
distances = ["dis_0", "dis_1", "dis_2", "dis_3", "dis_4"]
actions = ["forward", "backward", "right", "left", "stop"]


def random_color_transition():
    return random.choice(colors)


def random_distance_transition():
    return random.choice(distances)


# Function to simulate reward calculation based on transitions


def simulate_reward(prev_state, action, next_state):
    prev_color, prev_distance = prev_state
    next_color, next_distance = next_state
    distance_change = distances.index(next_distance) - distances.index(prev_distance)
    color_transition = determine_color_transition(prev_color, next_color)
    goal_achieved = next_color == "red" and next_distance == "dis_0"
    return (
        calculate_reward(distance_change, color_transition, goal_achieved, kd, kc, kg),
        goal_achieved,
    )


# Function to generate a synthetic dataset
def generate_fake_dataset(num_samples):
    dataset = []
    for _ in range(num_samples):
        prev_state = (random.choice(colors), random.choice(distances))
        action = random.choice(actions)
        next_state = (random_color_transition(), random_distance_transition())
        reward, goal_achieved = simulate_reward(prev_state, action, next_state)
        dataset.append((prev_state, action, next_state, reward, goal_achieved))
    return dataset


# Generate a fake dataset with 100 samples
fake_dataset = generate_fake_dataset(100)

# Export the dataset as text files
new_dir = "synth_random_data"
os.makedirs(new_dir, exist_ok=True)
index_file = os.path.join(new_dir, "index.txt")
if os.path.exists(index_file):
    with open(index_file, "r") as f:
        index = int(f.read())
else:
    index = 1
with open(os.path.join(new_dir, f"fake_random_dataset_{index}.txt"), "w") as f:
    for i, sample in enumerate(fake_dataset, start=1):
        f.write(f"{i}: {sample}\n")
with open(index_file, "w") as f:
    f.write(str(index + 1))

# # Print out some samples from the dataset
# for sample in fake_dataset[:10]:
#     print(sample)
