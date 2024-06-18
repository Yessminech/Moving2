#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <cstdlib> // For getenv
#include "functions/Drive.hpp"
#include "modules/sensors/ColorSensor.hpp"
#include "modules/sensors/DistanceSensor.hpp"

/// demo5 Yin

std::mutex mtx;
std::condition_variable cv;
bool command_running = false;
std::ofstream outputFile;

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
    
    // Distance sensor initialization
    DistanceSensor distanceSensor;
    int measuredDistance = distanceSensor.get_distance();    
    std::string distanceRange; 

    // Color sensor initialization
    ColorSensor colorSensor;
    auto measuredColor = colorSensor.get_color();
    std::string colorName;

    for (int i = 0; i < 10; i++) {
        measuredColor = colorSensor.get_color();

        float r = measuredColor.hue;  // These should be the RGB values
        float g = measuredColor.sat;  // These should be the RGB values
        float b = measuredColor.val;  // These should be the RGB values

        // Define ranges for each color
        const float blue_min_r = 0.0, blue_max_r = 100.0;
        const float blue_min_g = 0.0, blue_max_g = 150.0;
        const float blue_min_b = 150.0, blue_max_b = 255.0;

        const float black_min_r = 0.0, black_max_r = 80.0;
        const float black_min_g = 0.0, black_max_g = 80.0;
        const float black_min_b = 0.0, black_max_b = 80.0;

        const float red_min_r = 200.0, red_max_r = 255.0;
        const float red_min_g = 0.0, red_max_g = 100.0;
        const float red_min_b = 0.0, red_max_b = 100.0;

        const float white_min_r = 200.0, white_max_r = 1023.0;
        const float white_min_g = 200.0, white_max_g = 1023.0;
        const float white_min_b = 200.0, white_max_b = 1023.0;

        const float yellow_min_r = 200.0, yellow_max_r = 255.0;
        const float yellow_min_g = 200.0, yellow_max_g = 255.0;
        const float yellow_min_b = 0.0, yellow_max_b = 100.0;

        // Determine the color based on RGB values
        std::cerr << ">>> Measurement Color (r|g|b) : " << measuredColor.hue << " | " << measuredColor.sat << " | " << measuredColor.val << std::endl;

        if (r >= black_min_r && r <= black_max_r && g >= black_min_g && g <= black_max_g && b >= black_min_b && b <= black_max_b) {
            colorName = "Black";
        } else if (r >= white_min_r && r <= white_max_r && g >= white_min_g && g <= white_max_g && b >= white_min_b && b <= white_max_b) {
            colorName = "White";
        } else if (r >= red_min_r && r <= red_max_r && g >= red_min_g && g <= red_max_g && b >= red_min_b && b <= red_max_b) {
            colorName = "Red";
        } else if (r >= yellow_min_r && r <= yellow_max_r && g >= yellow_min_g && g <= yellow_max_g && b >= yellow_min_b && b <= yellow_max_b) {
            colorName = "Yellow";
        } else if (r >= blue_min_r && r <= blue_max_r && g >= blue_min_g && g <= blue_max_g && b >= blue_min_b && b <= blue_max_b) {
            colorName = "Blue";
        } else {
            colorName = "Unknown";
        }

        std::cout << "Detected Color: " << colorName << std::endl;

        // Loop for measuring distance
        measuredDistance = distanceSensor.get_distance();
        std::cerr << ">>> Measurement Distance : " << measuredDistance << std::endl;

        // Determine distance range
       
        if (measuredDistance <= 300) {
            distanceRange = "Dist_0";
        } else if (measuredDistance <= 600) {
            distanceRange = "Dist_1";
        } else if (measuredDistance <= 900) {
            distanceRange = "Dist_2";
        } else if (measuredDistance <= 1200) {
            distanceRange = "Dist_3";
        } else {
            distanceRange = "Dist_4";
        }

        std::cout << "Distance Range: " << distanceRange << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds{1000});

        std::cout << colorName << std::endl;
    outputFile << command << "," << angle << "," << colorName << "," << distanceRange << std::endl;
    }

    //std::cout << colorName << std::endl;
    //outputFile << command << "," << angle << "," << colorName << "," << distanceRange << std::endl;

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
    std::string homeDir = getenv("HOME");
    std::string filePath = homeDir + "/test/logging/commands_and_colors.csv";
    outputFile.open(filePath, std::ios::out | std::ios::app); 
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file at " << filePath << std::endl;
        return 1;
    }
    outputFile << "Command,Angle,Color,Distance\n";

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
        execute.join();
    }

    outputFile.close();
    return 0;
}
