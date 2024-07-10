# Moving2

## Description
This project is focused on the development of a robot that can move autonomously using Reinforcement Learning.

## How to use it ?

### Connect to SSH
  - Connect to "Free Wifi Berlin"
  - Run:
    ```bash
    ssh moving2@172.16.35.163
  - enter password: moving2024

  - How to get the IP address :
    - Open temrinal on Raspebrry pi and run on of this two options :
      - hostname -I
      - ifconfig
  
### Compile the code:
  - go into project folder and compile the code 
     - cd  hardware/code/libraries/buildhat++
     - cmake .
     - make
     - go into the executables with:
       - cd bin/
    
### Collect Data
  - ./drive_all_test
    - controll the robot by using:
      - 8 : forward
      - 2 : backward
      - 4 : left
      - 6 : right
    
  - update the filepath to collect data in "buildhat++/examples/moving2_src/drive_all_test.cpp" at line 397 an collect more data(10)
    
### Run Agent
  - ./agent_rpi
    
  




