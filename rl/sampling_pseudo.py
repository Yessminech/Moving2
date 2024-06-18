import time

# Define data collection parameters
num_episodes = 100
episode_length = 100
data = []

# Run random policy and collect data
for episode in range(num_episodes):
    for _ in range(episode_length):
        # Randomly choose action
        action = np.random.choice(num_actions)
        
        # Execute action on hardware (e.g., control motors)
        execute_action(action)
        
        # Read sensor data
        state = read_sensor_data()
        
        # Simulate reward (for example purposes)
        reward = simulate_reward(state)
        
        # Wait for a short time (optional)
        time.sleep(0.1)
        
        # Record data
        next_state = read_sensor_data()
        data.append((state, action, reward, next_state))

# Save collected data to a file
np.save('offline_data.npy', data)
