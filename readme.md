# Moving2

## Description
This project aims to develop a robot capable of autonomous locomotion using Reinforcement Learning.

## Project Structure
/Moving2

+-- README.md
+-- /documentation
|   +-- /control_system
|   +-- /rl_research
|   +--/milestones
|   +-- /tutorials
+-- /hardware
|   +--README.md
|   +-- /buildhat_firmware
|   +-- /code/libraries/buildhat++/examples/moving2_src
|   +--/legacy
+-- /rl
|   +-- /main
|   |   +-- README.md
|   |   +-- main.py
|   |   +-- env.py
|   |   +-- test.py
|   |   +-- synth_all.py
|   |   +--  Q_table.csv
|   |   +-- Q_table.npy
|   +-- /legacy

### Explanation:
- **/documentation**: Contains documentation files related to the project, such as design documents and user guides.
  - **/control_system**: Contains data-formatting guidelines
  - **/rl_research**: Contains research papers on choosing the rl Algorithm    
  - **/milestones**: Contains documentation/ slides for milestones presentations.
  - **/protocols**: Contains protocols of weekly meetings.
  - **/tutorials**: Contains tutorials on the coding style, setting-up the hardware and using GitHub, as wess as links to tutorials. 
- **/hardware**: Includes scripts and modules related to hardware components of the robot, such as motors, sensors, and actuators. The main hardware code for Moving-2 is under(`/hardware/code/libraries/buildhat++/examples/moving2_src`)
- **/rl**: Contains scripts for implementing Reinforcement Learning techniques, including training (`main.py`), evaluation (`test.py`) and robot environment setup (`env.py`).