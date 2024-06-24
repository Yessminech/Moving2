"""
Catch Game Experience Replay Class Definition

Python file containnig the Experience Replay class definitioin.

Authors: Sofie Verrewaere, Hiru Ranasinghe & Daniel Miskell @ Datatonic
"""

# ToDo In reinforcement learning, both approaches can be used, but they serve different purposes:
# 1. **Sequential [actions, observations] from start to end**: This approach is useful when the order of actions and their corresponding observations matter. This is often the case in tasks where the current action affects future states. For example, in your robot walking scenario, if the robot needs to learn how to balance itself while walking, then the sequence of actions and observations is important because an action taken at one time step affects the robot's balance at future time steps.
# 2. **Random [actions, observations]**: This approach is often used in conjunction with a technique called "experience replay" in reinforcement learning. The idea is to store the agent's experiences during the episode in a memory buffer and then sample a batch of experiences randomly from this buffer to train the model. This helps to break the correlation between consecutive experiences and stabilize the learning algorithm. In this case, the experiences don't need to be linked to each other.
# In your specific case of a robot walking in a straight line, if the goal is simply to move forward without any balancing or other complex tasks, then random [actions, observations] might be sufficient. However, if the task is more complex and involves maintaining balance or avoiding obstacles, then a sequence of [actions, observations] might be more appropriate.

import numpy as np
import keras
from typing import Tuple, Type


# experience replay buffer
# experience = previous state, the action taken, the next state transitioned to, the reward received, and the signal that it is done.
# list with max size. If nex experiences -> override
class ExperienceReplay(object):
    """
    A class to provide experience replay.
    Contains the initalization of the replay buffer with given parameters, a method to add_experience
    current state and a method to randomly select a batch of experiences for training
    the model.
    """

    # ToDo: init list
    def __init__(self, max_memory: int = 100, discount: float = 0.99) -> None:
        """
        Initialization of the experience buffer.

        Args:
            max_memory (int, optional): Maximum length of experience lookback saved. Defaults to 100.
            discount (float, optional): Discount factor applied to Q-value look ahead. Defaults to 0.9.
        """
        self.max_memory = max_memory
        self.memory = list()
        self.discount = discount

    # ToDo: add experience and overrite if max_memory reached

    def add_experience(self, sars: list, game_over: bool) -> None:
        """
        Memorize the current state of the game in the experience buffer.
        If max memory is reached delete oldest entry.

        Args:
            sars (List): [previous_state, action, reward, current_state]
            game_over (bool): Is game over True or False
        """
        self.memory.append([sars, game_over])
        if len(self.memory) > self.max_memory:
            del self.memory[0]

    # ToDo: read function description

    def get_qlearning_batch(
        self, model: Type[keras.Model], batch_size: int = 10
    ) -> Tuple[np.array, np.array]:
        """
        Randomly selects a batch of experiences (of size batch_size) from the saved
        experiences in self.memory, and returns the state inputs for each experience,
        along with the q-values for each experience for every possible action (left, stay, right).

        Args:
            model (tf.keras.Model): Sequential neural network for predicting Q-values.
            batch_size (int, optional): Batch size of inputs and targets to return. Defaults to 10.

        Returns:
            inputs (np.array), targets (np.array): state inputs to model, q-value from model for given state
        """
        memory_length = len(self.memory)
        number_of_actions = model.output_shape[-1]
        env_dim = self.memory[0][0][0].shape[1]

        # Placeholder for state inputs saved in the experience buffer
        inputs = np.zeros((min(memory_length, batch_size), env_dim))

        # Placeholder for target q-values after applying model to state input
        num_inputs = inputs.shape[0]
        targets = np.zeros((num_inputs, number_of_actions))

        # For each element in the batch of size batch_size randomly select an experience
        # save it into inputs, and calculate the q-values for state to be saved into
        # targets.
        ids = np.random.choice(memory_length, size=num_inputs, replace=False)

        # Select random experience
        sars = list(zip(*[self.memory[id_][0] for id_ in ids]))
        previous_states, action_ts, rewards, current_states = (
            np.concatenate(e) if isinstance(e[0], np.ndarray) else np.stack(e)
            for e in sars
        )
        game_over = np.stack([self.memory[id_][1] for id_ in ids])

        # Use state to calculate q-values for each action
        targets = model.predict(previous_states, batch_size=64, verbose=False)

        # Greedily choose maximum q-value
        Q_sa = np.max(model.predict(current_states, batch_size=64, verbose=False), 1)

        # Save into targets
        # If game_over is True use end reward
        # If not use current reward + discounted q-value
        # reward + gamma * max_a' Q(s', a')
        # reward is always zero in non terminal state, but is added for generality
        targets[np.arange(num_inputs), action_ts] = (
            rewards + self.discount * Q_sa * ~game_over
        )

        return previous_states, targets
