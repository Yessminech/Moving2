import numpy as np


def random_slice(array, slice_size):
    # Ensure the slice size is not larger than the array
    if slice_size > len(array):
        raise ValueError("Slice size cannot be larger than the array length.")

    # Calculate a random starting index
    start_index = np.random.randint(0, len(array) - slice_size + 1)

    # Obtain the slice
    return array[start_index:start_index + slice_size]
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