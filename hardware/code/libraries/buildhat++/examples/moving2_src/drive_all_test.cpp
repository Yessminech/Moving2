#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <Python.h>
#include <cstdlib> // For getenv
#include "functions/Drive.hpp"
#include "modules/sensors/ColorSensor.hpp"
#include "modules/sensors/DistanceSensor.hpp"

std::mutex mtx;
std::condition_variable cv;
bool command_running = false;
std::ofstream outputFile;






    std::string lastcolor = "white";
    std::string lastdistance = "dist_0";

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// use python to get goal_achieved  and calculate_reward




// Function to call the Python function goal_achieved
bool call_goal_achieved(const std::string& color, const std::string& distance) {
    // Initialize the Python interpreter
    Py_Initialize();

    // Set the Python script file name
    const char* script_name = "env";
    
    // Convert the file name to a Python string
    PyObject* pName = PyUnicode_DecodeFSDefault(script_name);

    // Import the Python module
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    bool result = false;

    if (pModule != nullptr) {
        // Get the function from the module
        PyObject* pFunc = PyObject_GetAttrString(pModule, "goal_achieved");

        // Check if the function is callable
        if (pFunc && PyCallable_Check(pFunc)) {
            // Create the argument tuple
            PyObject* pArgs = PyTuple_Pack(1, PyTuple_Pack(2, PyUnicode_FromString(color.c_str()), PyUnicode_FromString(distance.c_str())));

            // Call the function
            PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != nullptr) {
                result = PyObject_IsTrue(pValue);
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
                std::cerr << "Call failed" << std::endl;
            }
        } else {
            if (PyErr_Occurred()) PyErr_Print();
            std::cerr << "Cannot find function 'goal_achieved'" << std::endl;
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        std::cerr << "Failed to load '" << script_name << "'" << std::endl;
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return result;
}

// Function to call the Python function calculate_reward
double call_calculate_reward(const std::string& current_color, const std::string& current_distance, const std::string& next_color, const std::string& next_distance, bool goal) {
    // Initialize the Python interpreter
    Py_Initialize();

    // Set the Python script file name
    const char* script_name = "env";
    
    // Convert the file name to a Python string
    PyObject* pName = PyUnicode_DecodeFSDefault(script_name);

    // Import the Python module
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    double result = 0.0;

    if (pModule != nullptr) {
        // Get the function from the module
        PyObject* pFunc = PyObject_GetAttrString(pModule, "calculate_reward");

        // Check if the function is callable
        if (pFunc && PyCallable_Check(pFunc)) {
            // Create the argument tuple
            PyObject* pArgs = PyTuple_Pack(5, 
                                           PyUnicode_FromString(current_color.c_str()), 
                                           PyUnicode_FromString(current_distance.c_str()), 
                                           PyUnicode_FromString(next_color.c_str()), 
                                           PyUnicode_FromString(next_distance.c_str()), 
                                           goal ? Py_True : Py_False);

            // Call the function
            PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != nullptr) {
                result = PyFloat_AsDouble(pValue);
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
                std::cerr << "Call failed" << std::endl;
            }
        } else {
            if (PyErr_Occurred()) PyErr_Print();
            std::cerr << "Cannot find function 'calculate_reward'" << std::endl;
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        std::cerr << "Failed to load '" << script_name << "'" << std::endl;
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return result;
}














///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////




std::string get_action_name(int command) {
    switch (command) {
    case 8:
        return "forward";
    case 4:
        return "left";
    case 6:
        return "right";
    case 2:
        return "backward";
    default:
        return "Invalid";
    }
}

void execute_command(int command, double angle, Drive& drive) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        command_running = true;
    }

    std::string actionName = get_action_name(command);

    if (actionName == "Invalid") {
        std::cout << "Invalid command. Please use 8, 4, 6, or 2 with appropriate formatting.\n";
        {
            std::lock_guard<std::mutex> lock(mtx);
            command_running = false;
        }
        cv.notify_one();
        return;
    }

    std::cout << "Action: " << actionName << std::endl;

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

        const float brown_min_r = 80.0, brown_max_r = 160.0;
        const float brown_min_g = 50.0, brown_max_g = 120.0;
        const float brown_min_b = 0.0, brown_max_b = 80.0;

        // Determine the color based on RGB values
        std::cerr << ">>> Measurement Color (r|g|b) : " << measuredColor.hue << " | " << measuredColor.sat << " | " << measuredColor.val << std::endl;

        if (r >= black_min_r && r <= black_max_r && g >= black_min_g && g <= black_max_g && b >= black_min_b && b <= black_max_b) {
            colorName = "black";
        } else if (r >= white_min_r && r <= white_max_r && g >= white_min_g && g <= white_max_g && b >= white_min_b && b <= white_max_b) {
            colorName = "white";
        } else if (r >= red_min_r && r <= red_max_r && g >= red_min_g && g <= red_max_g && b >= red_min_b && b <= red_max_b) {
            colorName = "red";
        } else if (r >= yellow_min_r && r <= yellow_max_r && g >= yellow_min_g && g <= yellow_max_g && b >= yellow_min_b && b <= yellow_max_b) {
            colorName = "yellow";
        } else if (r >= blue_min_r && r <= blue_max_r && g >= blue_min_g && g <= blue_max_g && b >= blue_min_b && b <= blue_max_b) {
            colorName = "blue";
        } else if (r >= brown_min_r && r <= brown_max_r && g >= brown_min_g && g <= brown_max_g && b >= brown_min_b && b <= brown_max_b) {
            colorName = "brown";
        } else {
            colorName = "Unknown";
        }

        std::cout << "Detected Color: " << colorName << std::endl;

        // Loop for measuring distance
        measuredDistance = distanceSensor.get_distance();
        std::cerr << ">>> Measurement Distance : " << measuredDistance << std::endl;

        // Determine distance range
        if (measuredDistance <= 240) {
            distanceRange = "dist_4";
        } else if (measuredDistance <= 480) {
            distanceRange = "dist_3";
        } else if (measuredDistance <= 720) {
            distanceRange = "dist_2";
        } else if (measuredDistance <= 960) {
            distanceRange = "dist_1";
        } else if (measuredDistance <= 1200) {
            distanceRange = "dist_0";
        } else {
            distanceRange = "dist_out";
        }

        std::cout << "Distance Range: " << distanceRange << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds{1000});


///////////// use python code
///////
    std::string current_color = lastcolor;
    std::string current_distance = lastdistance;
    std::string next_color = colorName;
    std::string next_distance = distanceRange;
    bool achieved = call_goal_achieved(next_color, next_distance);
    //std::cout << "Goal achieved: " << (achieved ? "Yes" : "No") << std::endl;

    double reward = call_calculate_reward(current_color, current_distance, next_color, next_distance, achieved);
    //std::cout << "Reward: " << reward << std::endl;
//////

    std::string prevstate =   "(" + lastcolor + ", " + lastdistance + ")" ;
    outputFile << "(" << prevstate << ", " << actionName << ", (" << colorName << ", " << distanceRange << ")," << reward << "," << achieved ? "True" : "False"<< ")" << std::endl;


        lastdistance = distanceRange; 
        lastcolor = colorName;



    }


    
//1: (('white', 'dis_0'), 'forward', ('white', 'dis_0'), -1.0, False)


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
    std::string filePath = "/home/moving2/Moving2/hardware/code/libraries/buildhat++/examples/moving2_src/test/data0.csv";
    outputFile.open(filePath, std::ios::out | std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file at " << filePath << std::endl;
        return 1;
    }
    ///outputFile << "Command,Angle,Color,Distance\n";

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
