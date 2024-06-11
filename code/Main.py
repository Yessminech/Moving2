import numpy as np
import random
import os
from env import get_actions_length, get_colors_length, get_distances_length

##############################################################
#Defining Sizes of Components of Observation and Action spaces
##TODO align these with environment
observation_space_colors_n = get_colors_length()
observation_space_distances_n = get_distances_length()
action_space_n = get_actions_length()


#Initializing Q-Table
#Q_table has as its 1st Variable : current Color , 2nd : previous color
#3rd : current distance , 4th : previous distance, 5th : action
def initialize_Q_table():
    Q_table = np.zeros((observation_space_colors_n , observation_space_colors_n, observation_space_distances_n , observation_space_distances_n, action_space_n))
    return Q_table

# Define hyperparameters
learning_rate = 0.1 ##TODO Test different learning rates (0.7..)
discount_factor = 0.99
num_episodes = 1000 ##TODO Test different number of episodes (1000..) to increase dataset coverage
batch_size = 32

#Replay Buffer to store experiences
#TODO : define function to Import experience and store it in replay Buffer
def populate_replay_buffer(dataset):
    replay_buffer = []
    for experience in dataset:
        # Unpack the experience
        state, action, next_state, reward, goal = experience
        # Convert state and next_state to tuples
        state = tuple(state)
        next_state = tuple(next_state)
        # Append the modified experience to the replay buffer
        replay_buffer.append((state, action, next_state, reward, goal))
    return replay_buffer

def sample_batch(buffer, batch_size):
    return random.sample(buffer, min(len(buffer), batch_size))

#Function to update Q-table using a batch of experiences
def update_Q_table(Q_table, batch, learning_rate, discount_factor):
    for state, action, next_state, reward, goal in batch:
        curr_col, curr_dist = state
        next_col , next_dist = next_state

        # Q-learning update rule
        best_next_action = np.argmax(Q_table[curr_col, curr_dist , next_col , next_dist])
        td_target = reward + discount_factor * Q_table[curr_col, curr_dist , next_col , next_dist, best_next_action]
        td_error = td_target - Q_table[curr_col , curr_dist , next_col, next_dist, action]
        Q_table[curr_col, curr_dist , next_col , next_dist, action] += learning_rate * td_error
    return Q_table

#Training Loop
def train(replay_buffer, Q_table):
    for episode in range(num_episodes):

        #TODO : add experiences to replay buffer

        # Sample a batch of experiences from the replay buffer
        batch = sample_batch(replay_buffer, batch_size)

        # Update the Q-table using the batch
        update_Q_table(Q_table, batch, learning_rate, discount_factor)
    return Q_table

# Export the final Q_table
def export_Q_table(trained_Q_table):
    #Get path of the current file
    current_dir = os.path.dirname(os.path.realpath(__file__))
    Q_table_path = os.path.join(current_dir, 'Q_table.npy')
    # Save the Q_table
    try:
        np.save(Q_table_path, trained_Q_table)
        print(f"Q_table successfully saved at {Q_table_path}")
    except Exception as e:
        print(f"Failed to save Q_table at {Q_table_path}. Error: {e}")

##############################################################
## Testing 
# Simulate a fake dataset for testing
fake_dataset = [
    (('white', 'dis_0'), 'left', ('white', 'dis_1'), 1, False),
    (('white', 'dis_1'), 'forward', ('yellow', 'dis_2'), 10, False),
    (('yellow', 'dis_2'), 'forward', ('red', 'dis_2'), 20, True)
]
# Initialize the Q_table
Q_table = initialize_Q_table()
# Populate the replay buffer with the fake dataset
replay_buffer = populate_replay_buffer(fake_dataset)
# Train the Q_table using the replay buffer
trained_Q_table = train(replay_buffer, Q_table)
# Export the final Q_table
export_Q_table(trained_Q_table)
# Test the Q_table by printing a sample Q-value
sample_state = (1, 2, 3, 4)
sample_action = 0
q_value = trained_Q_table[sample_state][sample_action]
print(f"Q-value for state {sample_state} and action {sample_action}: {q_value}")