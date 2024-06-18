# Data Collection and Formatting Guidelines

This document outlines the required format for the data collected by the Raspberry Pi. Adhering to these guidelines will ensure seamless integration between the hardware and software components of our project.

## Observations

Observations should be a tuple of two elements: color and distance.

- `color`: This should be a string representing the color of the object. The possible values are: 'white', 'yellow', 'blue', 'red', 'black', 'brown'.
- `distance`: This should be a string representing the distance to the object. The possible values are: 'dis_out','dis_0', 'dis_1', 'dis_2', 'dis_3', 'dis_4'. Note that 'dis_4' represents a better(the smallest) distance than 'dis_0'. 'dis_out' is the biggest distance, covering out paths distances.

Example of an observation: `('red', 'dis_4')`

## Actions

Actions should be a string representing the action taken. The possible values are: 'forward', 'backward', 'right', 'left', 'stop'.

Example of an action: `'forward'`

## Dataset

The dataset should be a `.txt` file containing an ordered indexed list of tuples. Each tuple should represent a step in the environment and contain the following elements:
1. The current state (a tuple of `color` and `distance`)
2. The action taken
3. The next state (a tuple of `color` and `distance`)
4. The reward received
5. A boolean indicating whether the episode has ended

Example of a dataset:

```python
[
    1: (('white', 'dis_0'), 'forward', ('white', 'dis_0'), -1.0, False)
    2: (('yellow', 'dis_1'), 'backward', ('brown', 'dis_2'), 97.0, False)
    // ...
    3141: (('black', 'dis_0'), 'stop', ('black', 'dis_0'), -1.0, False)
]
```


Please ensure that the data is formatted as described above before sending it to our software. This will ensure that our software can correctly interpret and use the data.
