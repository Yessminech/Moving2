# Moving2

## Description
This project is focused on the development of a robot that can move autonomously using Reinforcement Learning.
## Project Structure Overview

- **`/Moving2/`**: The root directory of the project.
  - **`README.md`**: Provides a general overview and introduction to the directories organization.
  - **`/documentation/`**: Houses all the documentation related to the project, including research, design documents, and tutorials.
    - **`/control_system/`**: Contains information about the data formatting.
    - **`/rl_research/`**: Dedicated to Reinforcement Learning research.
    - **`/milestones/`**: Documents the project's progress and the milestones presentations.
    - **`/tutorials/`**: Provides tutorials related to the project on the hardwaren the coding style and version control usage.
  - **`/hardware/`**: Focuses on the physical components of the robot.
    - **`README.md`**: Specific details about the hardware requirements and setup.
    - **`/buildhat_firmware/buildhat++/examples/moving2_src/`**: The source code for the project utilizing the buildhat++ library.
    - **`/code/libraries/`**: Includes code that directly interacts with the robot's hardware.
    - **`/legacy/`**: Archives older or deprecated hardware files for historical reference.
  - **`/rl/`**: Contains all files related to the Reinforcement Learning code of the project.
    - **`/main/`**: The main directory for RL code, including scripts and data files.
      - **`README.md`**: An overview of the RL component, explaining its purpose and functionality.
      - **`main.py`**: The primary Python script for the RL model, orchestrating the learning process.
      - **`env.py`**: Defines the environment for the RL model.
      - **`test.py`**: Contains tests for the RL model.
      - **`synth_all.py`**: A script for synthesizing fake datasets.
      - **`Q_table.csv`**, **`Q_table.npy`**: Files containing the Q-table data, representing learned values for state-action pairs.
    - **`/legacy/`**: Stores older or deprecated RL files, providing a record of the project's evolution.
    - **`README.md`**: An overview of the RL repository.

## CI Pipeline
- The CI pipeline for this project includes formatting the code with Black and running tests to ensure code quality and functionality.
Before pushing the code, make sure to run `black .` to format it properly.
