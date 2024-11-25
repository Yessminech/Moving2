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
#include <string>
#include <signal.h>
#include <vector>

// developed from drive_all_test.cpp


//global variables for calculating index of q table
std::string prev_col;
std::string prev_dist;
//these are the colors before the last step

//std::mutex mtx;
//std::condition_variable cv;
bool command_running = false;
bool save_data = false;
std::ofstream outputFile;

//these are the colors that were measured after the last step and before the one we take now
std::string lastcolor = "white";
std::string lastdistance = "dist_0";
std::string actionName;

std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> Q_table;  //Q_Table

// fix remote from robert
bool STATUS_RUNNING = true;
/**
 * @brief Signal handler function.
 * 
 * This function is called when a signal is received. It performs the necessary cleanup and sets the STATUS_RUNNING flag to false.
 * 
 * @param signo The signal number.
 */
void sig_handler(int signo) {
    if (signo == SIGINT || signo == SIGQUIT || signo == SIGABRT || signo == SIGTERM || signo == SIGTSTP) {
        outputFile.close();
        STATUS_RUNNING = false;
        std::cout << "Received signal " << signo << ". Exiting..." << std::endl;
    }
}




/////////////////////////
/**
 * Checks if the goal is achieved based on the current color and distance.
 * 
 * @param current_color The current color.
 * @param current_distance The current distance.
 * @return True if the goal is achieved, false otherwise.
 */
bool goal_achieved(const std::string& current_color, const std::string& current_distance) {
/*     if(current_distance == "dist_4"){
        std::cout<< "okkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"<< std::endl;
    } */
    return current_color == "black" && current_distance == "dist_4";
}  
// Constants
const double kd = 1.0; // Distance reward factor
const double kc = 10.0; // Color reward factor
const double kg = 100.0; // Goal achievement reward

/**
 * Calculates the reward based on the current and next color, distance, and goal achievement.
 * 
 * @param current_color The current color.
 * @param current_distance The current distance.
 * @param next_color The next color.
 * @param next_distance The next distance.
 * @param goal_achieved Indicates whether the goal is achieved.
 * @param kd The distance coefficient (default value is kd).
 * @param kc The color coefficient (default value is kc).
 * @param kg The goal coefficient (default value is kg).
 * @return The calculated reward.
 */
double calculate_reward(const std::string& current_color, const std::string& current_distance, 
                        const std::string& next_color, const std::string& next_distance, 
                        bool goal_achieved, double kd = kd, double kc = kc, double kg = kg) {
    // Helper function to determine distance transition
    auto determine_distance_transition = [](const std::string& current_distance, const std::string& next_distance) -> std::string {
        // Implement your logic to determine the transition
        if (current_distance < next_distance) {
            return "better";
        } else if (current_distance > next_distance) {
            return "worse";
        } else {
            return "same";
        }
    };

    // Helper function to determine color transition
    auto determine_color_transition = [](const std::string& current_color, const std::string& next_color) -> std::string {
        // Implement your logic to determine the transition
        if (current_color == "red" && next_color == "blue") {
            return "better";
        } else if (current_color == "blue" && next_color == "red") {
            return "worse";
        } else {
            return "same";
        }
    };

    // Helper function to get distance value
    auto get_distance_value = [](const std::string& distance) -> double {
        // Implement your logic to get the distance value
        if (distance == "dist_0") {
            return 1.0;
        } else if (distance == "dist_1") {
            return 2.0;
        } else if (distance == "dist_2") {
            return 3.0;
        } else if (distance == "dist_3") {
            return 4.0;
        } else if (distance == "dist_4") {
            return 5.0;
        } else {
            return -10.0; // Default case
        }
    };

    // Helper function to get color value
    auto get_color_value = [](const std::string& color) -> double {
        // Implement your logic to get the color value
        if (color == "white") {
            return 1.0;
        } else if (color == "yellow") {
            return 2.0;
        } else if (color == "blue") {
            return 3.0;
        } else if (color == "red") {
            return 4.0;
        } else if (color == "black") {
            return 5.0;   
        }else if (color == "brown") {
            return -10.0;      
        }else {
            return 0.0; // Default case
        }
    };

    // Calculate R_distance
    std::string distance_change = determine_distance_transition(current_distance, next_distance);
    double R_distance = 0.0;
    if (distance_change == "better") {
        R_distance = kd * get_distance_value(next_distance);
    } else if (distance_change == "worse") {
        R_distance = -kd * get_distance_value(next_distance);
    }

    // Calculate R_color
    std::string color_transition = determine_color_transition(current_color, next_color);
    double R_color = 0.0;
    if (color_transition == "better") {
        R_color = kc * get_color_value(next_color);
    } else if (color_transition == "worse") {
        R_color = -kc * get_color_value(next_color);
    }

    // Calculate R_goal
    double R_goal = goal_achieved ? kg : 0.0;

    // Total reward
    double R = R_distance + R_color + R_goal;
    return R;
}


/////////////////////////
/////////////////////////       Q_TABLE 
/////////////////////////

// Function to read CSV into a 1D vector
std::vector<double> readCSV(const std::string& filename) {
    std::vector<double> data;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        
        while (std::getline(lineStream, cell, ',')) {
            if (!cell.empty()) {
                data.push_back(std::stod(cell));
            }
        }
    }
    
    file.close();
    return data;
}

// Function to reshape 1D vector into a 5D vector
/**
 * Reshapes a flat vector of data into a 5-dimensional vector.
 *
 * @param flatData The flat vector of data to be reshaped.
 * @param d1 The size of the first dimension.
 * @param d2 The size of the second dimension.
 * @param d3 The size of the third dimension.
 * @param d4 The size of the fourth dimension.
 * @param d5 The size of the fifth dimension.
 * @return The reshaped 5-dimensional vector.
 */
std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> reshapeTo5D(const std::vector<double>& flatData, int d1, int d2, int d3, int d4, int d5) {
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> data(d1, std::vector<std::vector<std::vector<std::vector<double>>>>(d2, std::vector<std::vector<std::vector<double>>>(d3, std::vector<std::vector<double>>(d4, std::vector<double>(d5)))));
    
    int index = 0;
    for (int i = 0; i < d1; ++i) {
        for (int j = 0; j < d2; ++j) {
            for (int k = 0; k < d3; ++k) {
                for (int l = 0; l < d4; ++l) {
                    for (int m = 0; m < d5; ++m) {
                        data[i][j][k][l][m] = flatData[index++];
                    }
                }
            }
        }
    }
    
    return data;
}


// Function to load and reshape the Q-table
/**
 * Loads a CSV file and reshapes the data into a 5-dimensional vector.
 * 
 * @param csvFilename The path to the CSV file.
 * @return A 5-dimensional vector containing the reshaped data.
 */
std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> loadAndReshapeQTable(const std::string& csvFilename) {
    std::vector<double> flatData = readCSV(csvFilename);
     // Define the dimensions of the original 5D table
    int d1 = 7;
    int d2 = 6;
    int d3 = 5;
    int d4 = 7;
    int d5 = 6;

    return reshapeTo5D(flatData, d1, d2, d3, d4, d5);
}

///// MAPPING : ACTIONS = ["forward", "backward", "right", "left", "stop"]


/////////////////////////
/////////////////////////       Q_TABLE 
/////////////////////////


/**
 * Returns the name of the action corresponding to the given command.
 *
 * @param command The command value representing the action.
 * @return The name of the action as a string.
 */
std::string get_action_name(int command) {
    switch (command) {
    case 0:
        return "forward";
    case 3:
        return "left";
    case 2:
        return "right";
    case 1:
        return "backward";
    default:
        return "Invalid";
    }
}

/**
 * Executes a command based on the given parameters. Considered to be a thread function.
 * 
 * @param command The command to execute.
 * @param angle The angle parameter for certain commands.
 * @param drive The Drive object used for controlling the movement.
 */
void execute_command(int command, double angle, Drive& drive) {
    //{
    //    std::lock_guard<std::mutex> lock(mtx);
    //    command_running = true;
    //}


    actionName = get_action_name(command);

    if (actionName == "Invalid" && command != 4) {
        std::cout << "Invalid command. Command from the table not in appropriate formatting.\n";
        //{
        //    std::lock_guard<std::mutex> lock(mtx);
        //    //command_running = false;
        //}
        //cv.notify_one();
        return;
    }

    //command contains the correct command already - maybe we want to change int command to string
    std::cout << "Action: " << actionName << std::endl;

    switch (command) {
    case 0:
        drive.set_speed(1);
        drive.move_forward(angle);
         // wait for one second
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
        // stop the drive
         drive.coast();
        break;
    case 3:
        drive.set_speed(0.5);
        drive.turn_left();
        // wait for one second
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
        // stop the drive
         drive.coast();
         save_data = true;
        break;
    case 2:
        drive.set_speed(0.5);
        drive.turn_right();
         // wait for one second
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
        // stop the drive
         drive.coast();
         save_data = true;
        break;
    case 1:
        drive.set_speed(1);
        drive.move_backward();
         // wait for one second
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
        // stop the drive
         drive.coast();
         save_data = true;
        break;
    case 4: //what is supposed to be done when the command is to stop?? is this sufficient
        drive.coast();
        break;
     default:
        std::cout << "Invalid command. Check q table if everything is correct with appropriate formatting.\n";
        return;    
    }

}


// Distance sensor initialization
DistanceSensor distanceSensor;
int measuredDistance = distanceSensor.get_distance();
std::string distanceRange;

// Color sensor initialization
ColorSensor colorSensor;
auto measuredColor = colorSensor.get_color();
std::string colorName;
    



            /////////////////// robert part sensor get ready
/**
 * @brief Reads sensor values and performs color and distance analysis.
 * 
 * This function continuously reads sensor values and analyzes the color and distance based on the RGB values.
 * It determines the color based on predefined ranges and assigns a color name accordingly.
 * It also determines the distance range based on predefined thresholds.
 * The color name, distance range, and other relevant information are printed to the console.
 * Additionally, it calculates the reward and saves the data if the save_data flag is set to true.
 * It is intended to be executed in a separate thread.
 * 
 * @note This function assumes that the colorSensor and distanceSensor objects have been properly initialized.
 * 
 * @note This function runs in a loop until the STATUS_RUNNING flag is false.
 */
void getSensorreading() {
        



    while (STATUS_RUNNING){ 
    
//for (int i = 0; i < 10; i++) {
    measuredColor = colorSensor.get_color();

    float r = measuredColor.hue;  // These should be the RGB values
    float g = measuredColor.sat;  // These should be the RGB values
    float b = measuredColor.val;  // These should be the RGB values

    // Define ranges for each color
    const float blue_min_r = 180.0, blue_max_r = 200.0;
    const float blue_min_g = 200.0, blue_max_g = 255.0;
    const float blue_min_b = 250.0, blue_max_b = 300.0;

    const float black_min_r = 0.0, black_max_r = 80.0;
    const float black_min_g = 0.0, black_max_g = 80.0;
    const float black_min_b = 0.0, black_max_b = 80.0;

    const float red_min_r = 200.0, red_max_r = 300.0;
    const float red_min_g = 0.0, red_max_g = 100.0;
    const float red_min_b = 100.0, red_max_b = 150.0;

    const float white_min_r = 500.0, white_max_r = 550.0;
    const float white_min_g = 500.0, white_max_g = 550.0;
    const float white_min_b = 500.0, white_max_b = 570.0;

    const float lila_min_r = 230.0, lila_max_r = 300.0;
    const float lila_min_g = 200.0, lila_max_g = 250.0;
    const float lila_min_b = 250.0, lila_max_b = 300.0;

    const float yellow_min_r = 400.0, yellow_max_r = 500.0;
    const float yellow_min_g = 300.0, yellow_max_g = 400.0;
    const float yellow_min_b = 200.0, yellow_max_b = 300.0;

    const float brown_min_r = 250.0, brown_max_r = 300.0;
    const float brown_min_g = 200.0, brown_max_g = 250.0;
    const float brown_min_b = 200.0, brown_max_b = 250.0;

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
    } else if (r >= lila_min_r && r <= lila_max_r && g >= lila_min_g && g <= lila_max_g && b >= lila_min_b && b <= lila_max_b) {
        colorName = "lila";    
    } else {
        continue;
        colorName = "Unknown";
        // continue;
    }

    std::cout << "Detected Color: " << colorName << std::endl;

    // Loop for measuring distance
    measuredDistance = distanceSensor.get_distance();
    std::cerr << ">>> Measurement Distance : " << measuredDistance << std::endl;

    // Determine distance range
    if (0 < measuredDistance &&  measuredDistance <= 240) {
        distanceRange = "dist_4";
    } else if (0 < measuredDistance && measuredDistance <= 480) {
        distanceRange = "dist_3";
    } else if (0 < measuredDistance && measuredDistance <= 720) {
        distanceRange = "dist_2";
    } else if (0 < measuredDistance &&  measuredDistance <= 960) {
        distanceRange = "dist_1";
    } else if (0 < measuredDistance && measuredDistance <= 1200) {
        distanceRange = "dist_0";
    } else if ( measuredDistance == -1) {
        distanceRange = "dist_out";    
    } else {
        distanceRange = "dist_out";
    }

    std::cout << "Distance Range: " << distanceRange << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    // Use Python code
    std::string current_color = lastcolor;
    std::string current_distance = lastdistance;
    std::string next_color = colorName;
    std::string next_distance = distanceRange;



    //function to calculate goal
    
    bool achieved = goal_achieved(colorName, distanceRange);  
    //std::cout << "Goal achieved: " << (achieved ? "Yes" : "No") << std::endl;



    double reward = calculate_reward(current_color, current_distance, next_color, next_distance, achieved, kd, kc, kg);
    //std::cout << "Reward: " << reward << std::endl;
    
    if( save_data == true ){
    std::string prevstate = "(" + lastcolor + ", " + lastdistance + ")" ;
    outputFile << "(" 
            << prevstate 
            << ", " << actionName 
            << ", (" << colorName << ", " << distanceRange 
            << "), " << reward 
            << ", " << (achieved ? "True" : "False") 
            << ")" << std::endl;
    prev_col=lastcolor;
    prev_dist = lastdistance;
    save_data = false;
    }
    lastdistance = distanceRange; 
    lastcolor = colorName;


    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    /* drive.coast();

    {
        std::lock_guard<std::mutex> lock(mtx);
        command_running = false;
    }
    cv.notify_one(); */
    }
}

/**
 * Finds the index of the maximum value in the Q_table for a given state.
 * 
 * @param curr_col The current column index.
 * @param curr_dist The current distance index.
 * @param prev_col The previous column index.
 * @param prev_dist The previous distance index.
 * @param actions The number of actions.
 * @return The index of the maximum value in the Q_table.
 */
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


/**
 * Returns the distance value based on the provided distance string.
 *
 * @param distance The distance string to be evaluated.
 * @return The corresponding distance value.
 */
int get_distance_conforms(std::string distance) {
    // Implement your logic to get the distance value
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
    }else {
    return 10;
    }
 };

/**
 * Returns the color conformity value based on the given color.
 *
 * @param color The color to check conformity for.
 * @return The color conformity value. Returns 0 for "white", 1 for "yellow",
 *         2 for "blue", 3 for "red", 4 for "black", 5 for "brown", 6 for "lila",
 *         and 10 for any other color.
 */
int get_color_conforms(std::string color){
    // Implement your logic to get the color value
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
    }else if (color == "brown") {
        return 5;
    }else if (color == "lila") {
        return 6;
    }else{
    return 10; //default case for when color has no match
    }
};

/**
 * @brief The main function of the program.
 *
 * This function is the entry point of the program. It registers signal handlers for Ctrl+C, Ctrl+Z, and other signals.
 * It opens a file for writing and checks if the file was opened successfully. It initializes variables and starts a thread
 * for sensor reading. It enters a loop and performs actions based on sensor readings. Finally, it closes the file and returns 0.
 *
 * @return 0 if the program executed successfully, 1 otherwise.
 */
int main() {

    // register signal Ctrl+C and Ctrl+Z and some other signals
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGTSTP, sig_handler);


    auto& drive = Drive::getInstance();
    std::string filePath = "/home/moving2/Moving2/hardware/code/libraries/buildhat++/examples/moving2_src/test/data1.csv";
    outputFile.open(filePath, std::ios::out | std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file at " << filePath << std::endl;
        return 1;
    }
    ///outputFile << "Command,Angle,Color,Distance\n";

    std::string input;
    double angle = 0;
    int command_value;
    int actions = 4;

    /*std::cout << "Control the car with keyboard input.\n";
    std::cout << "Use format like '8,10' for forward with an angle, '4' for left, '6' for right, '2' for backward and 5 for stop.\n";
    std::cout << "CTRL + C and CTRL + Z close the program.\n";*/
    std::thread sensing(getSensorreading);

    Q_table = loadAndReshapeQTable("/home/moving2/Moving2/hardware/code/libraries/buildhat++/examples/moving2_src/Q_table.csv");


    
    while (STATUS_RUNNING) {
        //std::unique_lock<std::mutex> lock(mtx);
        //cv.wait(lock, [] { return !command_running; });

        //this is a little confusing, but lastcolor and lastdistance are last measured values, so CURRENT values,
        // and prev_col and prev_dist are the previously measured(before the last step) values
        int curCol = get_color_conforms(lastcolor);
        int lastCol = get_color_conforms(prev_col);
        int lastDis = get_distance_conforms(prev_dist);
        int curDis = get_distance_conforms(lastdistance);
        //for debugging
        if(curCol > 6 || lastCol > 6){
            std::cerr << "Color out of range" << std::endl;
        }
        if(curDis == -10 || lastDis == -10){
            std::cerr << "Distance out of range - default dist_out" << std::endl;
        }
        if(curDis == 10 || lastDis == 10){
            std::cerr << "unexpected value in distance" << std::endl;
        }

        command_value = argmax(curCol, curDis, lastCol, lastDis, actions);

        //lock.unlock();
        std::thread execute(execute_command, command_value, angle, std::ref(drive));
        
        execute.join();
    }
    sensing.join();

    outputFile.close();
    return 0;
}
