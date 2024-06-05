import numpy as np
import random

##############################################################
#Defining Sizes of Components of Observation and Action spaces
observation_space_colors_n = 7
observation_space_distances_n = 10
action_space_n = 3


#Initializing Q-Table
#Q_table has as its 1st Variable : current Color , 2nd : previous color
#3rd : current distance , 4th : previous distance, 5th : action
Q_table = np.zeros((observation_space_colors_n , observation_space_colors_n , observation_space_distances_n , observation_space_distances_n, action_space_n))

# Define hyperparameters
learning_rate = 0.1
discount_factor = 0.99
num_episodes = 1000
batch_size = 32

#Replay Buffer to store experiences
replay_buffer = []

#TODO : define function to Import experience and store it in replay Buffer

def sample_batch(buffer, batch_size):
    return random.sample(buffer, min(len(buffer), batch_size))


#Function to update Q-table using a batch of experiences
def update_q_table(Q_table, batch, learning_rate, discount_factor):
    for state, action, reward, next_state in batch:
        curr_col, prev_col , curr_dist , prev_dist  = state
        next_curr_col, next_prev_col , next_curr_dist , next_prev_dist = next_state

        # Q-learning update rule
        best_next_action = np.argmax(Q_table[next_curr_col, next_prev_col , next_curr_dist , next_prev_dist])
        td_target = reward + discount_factor * Q_table[next_curr_col, next_prev_col , next_curr_dist , next_prev_dist, best_next_action]
        td_error = td_target - Q_table[curr_col, prev_col , curr_dist , prev_dist, action]
        Q_table[curr_col, prev_col , curr_dist , prev_dist, action] += learning_rate * td_error



#Training Loop
for episode in range(num_episodes):

    #TODO : add experiences to replay buffer

    # Sample a batch of experiences from the replay buffer
    batch = sample_batch(replay_buffer, batch_size)

    # Update the Q-table using the batch
    update_q_table(Q_table, batch, learning_rate, discount_factor)

#TODO : export the final Q_table