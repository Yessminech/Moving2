#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "functions/Drive.hpp" 
std::mutex mtx;
std::condition_variable cv;
bool command_running = false; 

void execute_command(int command, double angle, Drive& drive) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        command_running = true;
    }

    switch (command) {
    case 8:
        drive.set_speed(0.5);
        drive.move_forward(angle);
        break;
    case 4:
        drive.set_speed(0.5);
        drive.turn_left();
        break;
    case 6:
        drive.set_speed(0.5);
        drive.turn_right();
        break;
    case 2:
        drive.set_speed(0.5);
        drive.move_backward();
        break;
    default:
        std::cout << "Invalid command. Please use 8, 4, 6, or 2 with appropriate formatting.\n";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    drive.coast();

    {
        std::lock_guard<std::mutex> lock(mtx);
        command_running = false;
    }
    cv.notify_one();
}

int main() {
    auto& drive = Drive::getInstance();
    std::string input;
    int command;
    double angle = 0;

    std::cout << "Control the car with keyboard input.\n";
    std::cout << "Use format like '8,10' for forward with an angle, '4' for left, '6' for right, '2' for backward.\n";

    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !command_running; }); 

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

        lock.unlock(); 
        std::thread execute(execute_command, command, angle, std::ref(drive));
        execute.detach(); 
    }

    return 0;
}

