import numpy as np
from collections import deque
import random

def random_slice(deque_obj, slice_size: int):
    # Ensure the slice size is not larger than the deque
    if slice_size > len(deque_obj):
        raise ValueError("Slice size cannot be larger than the deque length.")

    # Calculate a random starting index
    start_index = random.randint(0, len(deque_obj) - slice_size)

    # Obtain the slice
    return [deque_obj[i] for i in range(start_index, start_index + slice_size)]
def read_text_file(file_path):
    with open(file_path, 'r') as file:
        return file.read()
def text_to_table(file_path):
    #read file
    raw_data = read_text_file(file_path)

    # Split the raw data into lines
    lines = raw_data.split('\n')

    # Parse the data into a list of tuples
    data = []
    for line in lines:
        index, content = line.split(': ', 1)
        current_state, action, next_state, reward, done = eval(content)
        data.append((current_state, action, next_state, reward, done))