#include "argmaxtest.h"

#include <iostream>
#include <cassert>

    const int currColor = 7;
    const int currDist = 6;
    const int possibleActions = 5;
    const int prevColor = 7;
    const int prevDist = 6;

    double Q_table[currColor][currDist][possibleActions][prevColor][prevDist];

    void initialize_Q_table_distinct() {
        for (int i = 0; i < currColor; ++i) {
            for (int j = 0; j < currDist; ++j) {
                for (int k = 0; k < possibleActions; ++k) {
                    for (int l = 0; l < prevColor; ++l) {
                        for (int m = 0; m < prevDist; ++m) {
                            // Adding some non-integer values for testing
                            Q_table[i][j][k][l][m] = static_cast<double>(i + j + k + l + m) + 0.3 * (i + j + k + l + m) / 10;
                        }
                    }
                }
            }
        }
    }

void initialize_Q_table_same() {
        for (int i = 0; i < currColor; ++i) {
            for (int j = 0; j < currDist; ++j) {
                for (int k = 0; k < possibleActions; ++k) {
                    for (int l = 0; l < prevColor; ++l) {
                        for (int m = 0; m < prevDist; ++m) {
                            // Adding the same value for testing
                            Q_table[i][j][k][l][m] = 1.0;
                        }
                    }
                }
            }
        }
    }

void initialize_Q_table_negative() {
        for (int i = 0; i < currColor; ++i) {
            for (int j = 0; j < currDist; ++j) {
                for (int k = 0; k < possibleActions; ++k) {
                    for (int l = 0; l < prevColor; ++l) {
                        for (int m = 0; m < prevDist; ++m) {
                            // Adding negative values for testing
                            Q_table[i][j][k][l][m] = (static_cast<double>(i + j + k + l + m) + 0.7 * (i + j + k + l + m) / 10)*-1;
                        }
                    }
                }
            }
        }
    }

void initialize_Q_table_large() {
        for (int i = 0; i < currColor; ++i) {
            for (int j = 0; j < currDist; ++j) {
                for (int k = 0; k < possibleActions; ++k) {
                    for (int l = 0; l < prevColor; ++l) {
                        for (int m = 0; m < prevDist; ++m) {
                            // Adding large values for testing
                            Q_table[i][j][k][l][m] = (static_cast<double>(i + j + k + l + m) + 0.7 * (i + j + k + l + m) / 10)*1000000;
                        }
                    }
                }
            }
        }
    }

    int argmax(int curr_col, int curr_dist, int prev_col, int prev_dist, int actions) {
        int best_index = 0;
        double max_value = Q_table[curr_col][curr_dist][0][prev_col][prev_dist];

        for (int i = 1; i < actions; ++i) {
            if (Q_table[curr_col][curr_dist][i][prev_col][prev_dist] > max_value) {
                max_value = Q_table[curr_col][curr_dist][i][prev_col][prev_dist];
                best_index = i;
            }
        }
        return best_index;
    }

void test_argmax() {
        // Initialize Q_table with sample values
        initialize_Q_table_distinct();

        //Test 1: finds best index in table with distinct values
        //also: tests maximum index
        int curr_col = 2;
        int curr_dist = 3;
        int prev_col = 1;
        int prev_dist = 4;
        int actions = possibleActions;

        int best_index = argmax(curr_col, curr_dist, prev_col, prev_dist, actions);
        int expected_best_index = actions - 1;
        assert(best_index == expected_best_index);

        //Test 2: all the values are the same
        initialize_Q_table_same();
        int best_index2 = argmax(curr_col, curr_dist, prev_col, prev_dist, actions);
        int expected_best_index2 = 0.0;
        assert(best_index2 == expected_best_index2);

        //Test 3: the values are negative
        initialize_Q_table_negative();
        int best_index3 = argmax(curr_col, curr_dist, prev_col, prev_dist, actions);
        int expected_best_index3 = 0.0;
        assert(best_index3 == expected_best_index3);

        //Test 4: The values are large
        initialize_Q_table_large();
        int best_index4 = argmax(curr_col, curr_dist, prev_col, prev_dist, actions);
        int expected_best_index4 = actions - 1;
        assert(best_index4 == expected_best_index4);

        //Test 5: Max index
        initialize_Q_table_large();
        curr_col = 6;
        curr_dist = 5;
        prev_col = 6;
        prev_dist = 5;
        actions = possibleActions;
        int best_index5 = argmax(curr_col, curr_dist, prev_col, prev_dist, actions);
        int expected_best_index5 = actions - 1;
        assert(best_index5 == expected_best_index5);

        std::cout << "argmax function test passed!" << std::endl;
    }

int main() {
    test_argmax();
    return 0;
}

