#include <iostream>
#include <sstream>
#include <thread>
#include "functions/Drive.hpp"


int main() {
   
    auto& drive = Drive::getInstance();

    std::string input;    
    int command;          
    double angle = 0;     
    double speed = 0.5;

    std::cout << "Control the car with keyboard input.\n";
    std::cout << "Use format like '8,10' for forward with an angle, '4' for left, '6' for right, '2' for backward.\n";

    while (true) {
        std::cout << "Enter command (e.g., '8,10' or '4'): ";
        std::getline(std::cin, input); 

        
        std::istringstream iss(input);
        std::string part;
        if (std::getline(iss, part, ',')) {
            std::istringstream(part) >> command; 

            if (std::getline(iss, part)) {
                std::istringstream(part) >> angle; 
            } else {
                angle = 0; 
            }
        }

        switch (command) {
        case 8:
            drive.set_speed(speed); 
            drive.move_forward(angle);
            break;
        case 4:
            drive.set_speed(speed); 
            drive.turn_left();
            break;
        case 6:
            drive.set_speed(speed); 
            drive.turn_right();
            break;
        case 2:
            drive.set_speed(speed); 
            drive.move_backward();
            break;
        default:
            std::cout << "Invalid command. Please use 8, 4, 6, or 2 with appropriate formatting.\n";
            continue;
        }

        std::cout << "Operation in progress...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds{1000}); 

        drive.coast(); 
        std::cout << "Operation completed. Enter next command.\n";
    }

    return 0;
}
