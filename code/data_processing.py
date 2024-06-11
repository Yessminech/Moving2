import numpy as np

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