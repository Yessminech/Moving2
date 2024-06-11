#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <string>
#include <ctime>
#include "functions/Drive.hpp"
#include "modules/sensors/ColorTypes.hpp"
#include "modules/sensors/ColorSensor.hpp"

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
    case 2: //we can try if this works but the library wasn't set up to drive our robot so this might not do what we intended
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

int get_color_data(int thread_id, ColorSensor colorsense){
    Color::Color color = colorsense.get_color(); //Q does this need to be in the same function as ColorSensor colorsense? Or otherwise can I make colorsense global

    // how do we want to handle errors??
    if(color.is_empty()) {
    std::cerr << "Error: sensor data not available, too short or no color" << std::end
    }

    //here, the data from the distance sensor needs to be collected

    //here, a function needs to be called, that writes threadid, previous sensor data, action and current sensor data into a line in the file
}


/**
* @param threadId for debugging and validation of data
* @param command input to CSV file
* @param file_path filename to write data into
* @param colorsense colorsensor instance
*/
void get_data_file(int threadId, int command, const std::string &file_path, ColorSensor colorsense){
    std::ofstream file;

    //here call the sensor functions
    Color::color get_color_data(threadId, colorsense);

    //append content to file
    file.open(file_path, std::ios::app);
    if(!file.is_open()) {
    std:cerr << "Error: problem opening file." << file_path << std::endl;
    return;
    }
    //write everything into the file, missing yet: distance sensor data
    file << threadId << "," << command << "," << color.hue << "," << color.sat << "," << color.val << "\n";

    file.close();

}

/**
* returns a filename that contains time, for easier usage of collected data
* @return filename
*/
std::string new_filename(const std::string& directory) {

    std:: time_t now = std::time(nullptr);
    std::tm* time_now = std::localtime(&now);
    std::string path = "home/buildhat++"; //NEEDS TO BE ADJUSTED TO ACTUAL DIRECTORY ON RPI!!!

    std::ostringstream stringstr
    stringstr << std::put_time(time_now, "%Y-%m-%d_%H-%M-%S");

    std::string filename = path + "/data" + stringstr.str() + ".csv";
    return filename;
}

int main() {
    auto& drive = Drive::getInstance();
    std::string input;
    int command;
    double angle = 0;
    ColorSensor colorsense;
    //returns filename that contains date and time for easier usage of collected data
    std::string filename = new_filename();

    //create file
    std::ofstream file(file_path);
    if (!file.is_open()) {
    std::cerr << "Error: Could not create file" << file_path << std::endl;
    return 1;
    }


    std::cout << "Control the robot with keyboard input.\n";
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

    //do both of these here
    /**
    * @param: threadId(?), command, filepath
*/
    get_data_file(threadId, command, filename, colorsense);
   //call sensor function (inside thread???
   //write data to the file


    return 0;
}

