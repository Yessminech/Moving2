# Moving2

## Description
This project is focused on the development of a robot that can move autonomously using Reinforcement Learning.

## How to use HW 

### Connect to SSH
  - Connect to "Free Wifi Berlin"
  - Run:
    ```bash
    ssh moving2@172.16.35.163
    ```
  - Enter password: moving2024.

### Finding the IP address:
To find the IP address of your Raspberry Pi:
- Open a terminal on the Raspberry Pi.
- Use one of the following commands:
  ```bash
  hostname -I
  #or
  ifconfig
  ```
  
### Compile the code:
1 - Navigate to the project folder:
  ```bash
  cd hardware/code/libraries/buildhat++
  ```
2 - Compile the code   
  ```bash
  cmake .
  make
  ```
3 - Navigate to the executables:    
   ```bash
   cd bin/
   ```

### Collect Data
To collect data for training the robot:
- Run the data collection script:
```bash
./drive_all_test
```
  
- Update the file path to collect more data (10) in
  ***buildhat++/examples/moving2_src/drive_all_test.cpp***, line 397.

An example output of the console is in documentation/milestones/Milestone 3/example output terminal.
    
### Run Agent
To run the autonomous agent on the Raspberry Pi:
- Execute the agent
```bash
./agent_rpi
```
#### Testing
To run testing for the argmax function: 
- Compile (for instance like this)
```bash
g++ -o argmaxtest argmaxtest.cpp
```
- Execute
```bash
./argmaxtest
```

## How to use RL

### Compute Q_table and export it to .csv
```bash
python main.py
```
An example output of the console is in exp_out.png.

#### Changing Parameters for RL-Algorithm
Learning rate: learning_rate (default: 0.5)
Discount factor: discount_factor (default: 0.99)
Number of episodes: num_episodes (default: 10000)
Batch size: batch_size (default: 32)

#### Changing Parameters for RL-Algorithm
- **Learning rate**: `learning_rate` (default: 0.5)
- **Discount factor**: `discount_factor` (default: 0.99)
- **Number of episodes**: `num_episodes` (default: 10000)
- **Batch size**: `batch_size` (default: 32)

#### Adding New Datasets
Add new datasets under `hardware/code/libraries/buildhat++/examples/moving2_src/test/` in the format specified in `documentation/control_system/Data_Collection_Guidelines.md`.

#### Policy Evaluation
Add the desired evaluator under `def train(self)`:
- `plot_rewards_over_batches`
- `plot_average_rewards_over_episodes`
- `get_best_action`
- [`get_max_q`](command:_github.copilot.openSymbolFromReferences?%5B%7B%22%24mid%22%3A1%2C%22path%22%3A%22%2Fhome%2Fyessmine%2FStudies%2F6Semester%2FProject%2FMoving2%2Frl%2Fmain%2Fpolicy_evaluator.py%22%2C%22scheme%22%3A%22file%22%7D%2C%7B%22line%22%3A38%2C%22character%22%3A8%7D%5D "policy_evaluator.py")
- `number_of_steps_from_start`
- `plot_values_distribution`

#### Adding New Datasets
Add new datasets under hardware/code/libraries/buildhat++/examples/moving2_src/test/ in the format specified in documentation/control_system/Data_Collection_Guidelines.md.

#### Policy Evaluation
Add the desired evaluator under def train(self):

plot_rewards_over_batches
plot_average_rewards_over_episodes
get_best_action
get_max_q
number_of_steps_from_start
plot_values_distribution

#### Default Evaluators
```python
PolicyEvaluator.plot_rewards_over_batches(self.rewards)
PolicyEvaluator.plot_average_rewards_over_episodes(self.rewards, self.num_episodes)
PolicyEvaluator.plot_values_distribution(self.Q_table)
```
#### Testing
```bash
python test_main.py
```
