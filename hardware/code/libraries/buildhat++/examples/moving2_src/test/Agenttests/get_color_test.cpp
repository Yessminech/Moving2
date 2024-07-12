#include "get_color_test.h"
#include <iostream>
#include <cassert>

// Tests get_color_conforms
int get_color_conforms(std::string color) {
    if (color == "white") {
        return 0;
    } else if (color == "yellow") {
        return 1;
    } else if (color == "blue") {
        return 2;
    } else if (color == "red") {
        return 3;
    } else if (color == "black") {
        return 4;
    } else if (color == "brown") {
        return 5;
    } else if (color == "lila") {
        return 6;
    } else {
        return 10; // Default case for when color has no match
    }
}

// Test cases
void test_get_color_conforms() {
    // Valid cases
    assert(get_color_conforms("white") == 0);
    assert(get_color_conforms("yellow") == 1);
    assert(get_color_conforms("blue") == 2);
    assert(get_color_conforms("red") == 3);
    assert(get_color_conforms("black") == 4);
    assert(get_color_conforms("brown") == 5);
    assert(get_color_conforms("lila") == 6);

    // Invalid cases
    assert(get_color_conforms("") == 10);
    assert(get_color_conforms("unknown") == 10);
    assert(get_color_conforms("green") == 10);
    assert(get_color_conforms("123") == 10);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_get_color_conforms();
    return 0;
}

