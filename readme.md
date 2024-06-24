# Moving2

## Description
This project aims to develop a robot capable of autonomous locomotion using Reinforcement Learning.

## Project Structure
/Moving2
│
├── /documentation
│ ├── /control_system
│ ├── /rl_research
│ ├── /milestones
│ └── /tutorials
│
├── /hardware
│ ├── README.md
│ ├── train.py
│ ├── evaluate.py
│ ├── rl_agent.py
│ └── robot_environment.py
│
├── /rl
│ ├── /design-docs
│ │ ├── architecture.md
│ │ └── diagrams
│ └── /tutorials
│
└── /workflow
├── pre-processing.py
├── analysis.py
└── visualization.py

### Explanation:
- **/documentation**: Contains documentation files related to the project, such as design documents and user guides.
  - **/control_system**: Contains data-formatting guidelines
  - **/rl_research**: Contains research papers on choosing the rl Algorithm    
  - **/milestones**: Contains documentation/ slides for milestones presentations.
  - **/protocols**: Contains protocols of weekly meetings.
  - **/tutorials**: Contains tutorials on the coding style, setting-up the hardware and using GitHub, as wess as links to tutorials. 
- **/hardware**: Includes scripts and modules related to hardware components of the robot, such as motors, sensors, and actuators.
- **/rl**: Contains scripts for implementing Reinforcement Learning techniques, including training (`main.py`), evaluation (`test.py`) and robot environment setup (`env.py`).
- **/workflow**: Includes .yaml files related to CI pipeline.

