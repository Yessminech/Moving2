#include "get_distance_test.h"
#include <iostream>
#include <cassert>

//tests get_distance_conforms
int get_distance_conforms(std::string distance) {
    if (distance == "dist_0") {
        return 0;
    } else if (distance == "dist_1") {
        return 1;
    } else if (distance == "dist_2") {
        return 2;
    } else if (distance == "dist_3") {
        return 3;
    } else if (distance == "dist_4") {
        return 4;
    } else if (distance == "dist_out") {
        return -10; // Default case
    } else {
        return 10; // Default case for unexpected input
    }
}

// Test cases
void test_get_distance_conforms() {
    // valid cases
    assert(get_distance_conforms("dist_0") == 0);
    assert(get_distance_conforms("dist_1") == 1);
    assert(get_distance_conforms("dist_2") == 2);
    assert(get_distance_conforms("dist_3") == 3);
    assert(get_distance_conforms("dist_4") == 4);
    assert(get_distance_conforms("dist_out") == -10);

    // invalid cases
    assert(get_distance_conforms("") == 10);
    assert(get_distance_conforms("unknown") == 10);
    assert(get_distance_conforms("dist_5") == 10);
    assert(get_distance_conforms("3") == 10);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_get_distance_conforms();
    return 0;
}

