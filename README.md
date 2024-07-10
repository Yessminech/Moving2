# Moving2

## Description
This project is focused on the development of a robot that can move autonomously using Reinforcement Learning.

## How to use it ?

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
    - Use one of the following commands
      ```bash
      hostname -I
      #or
      ifconfig
      ```
  
### Compile the code:
  1 - Navigate to the project folder:
      ```bash
      cd hardware/code/libraries/buildhat++
  2 - Compile the code   
      ```bash
      cmake .
      make
  3 -Navigate to the executables:    
     ```bash
     cd bin/
    
### Collect Data
To collect data for training the robot:
  - Run the data collection script:
  ```bash
  ./drive_all_test
      Control the robot using the following keys:
      - 8 : forward
      - 2 : backward
      - 4 : left
      - 6 : right
    
  - Update the file path to collect more data (10) in
    buildhat++/examples/moving2_src/drive_all_test.cpp, line 397.
  
    
### Run Agent
To run the autonomous agent on the Raspberry Pi:
  - Execute the agent
  ```bash
  ./agent_rpi
    
  




