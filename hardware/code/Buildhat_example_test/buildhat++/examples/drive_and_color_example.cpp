/*#include <thread>
#include <cstdlib>
#include "functions/Drive.hpp"
#include "modules/sensors/ColorSensor.hpp"

void colorThread(){
    ColorSensor colorSensor;
    for (int i = 0; i < 10; i++)
    {        
        auto measuredColor = colorSensor.get_color();  
        std::cerr << ">>> Measurement : " << measuredColor << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
    
}

int main() {
    // get a reference to the drive
    auto drive = Drive::getInstance();
    std::thread thread(colorThread);
    // init Color sensor

    // drive forward for one second with 50% speed
    //drive.set_speed(0.6);
    //drive.move_forward(0);

    // wait for one second
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    //drive.move_forward(45);

    // wait for one second
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    //drive.move_forward(-45);

    // wait for one second
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    // stop the drive
    drive.coast();
    thread.join();
}
*/



// test code************************************+++
// test code************************************+++
// test code************************************+++
// test code************************************+++
// test code************************************+++

// test code************************************+++
// test code************************************+++
// test code************************************+++
// test code************************************+++


/*
#include <thread>
#include <iostream>
#include <chrono>
#include "functions/Drive.hpp"
#include "modules/sensors/ColorSensor.hpp"

void colorThread() {
    ColorSensor colorSensor;
    for (int i = 0; i < 10; i++) {
        auto measuredColor = colorSensor.get_color();
        
        // Assuming measuredColor contains hue, saturation, and value components
        float r = measuredColor.hue;
        float g = measuredColor.sat;
        float b = measuredColor.val;

        std::string colorName;

        // Define ranges for each color
        //const float red_min_hue = 0.0, red_max_hue = 20.0;
        //const float yellow_min_hue = 30.0, yellow_max_hue = 60.0;
        //const float blue_min_hue = 200.0, blue_max_hue = 250.0;
        const float blue_min_r = 200.0, blue_max_r = 220.0;
        const float blue_min_g = 240.0, blue_max_g = 270.0;
        const float blue_min_b = 250.0, blue_max_b = 290.0;

        const float black_min_r = 0.0, black_max_r = 80.0;
        const float black_min_g = 0.0, black_max_g = 80.0;
        const float black_min_b = 0.0, black_max_b = 80.0;

        const float red_min_r = 230.0, red_max_r = 290.0;
        const float red_min_g = 60.0, red_max_g = 110.0;
        const float red_min_b = 80.0, red_max_b = 130.0;

        const float white_min_r = 520.0, white_max_r = 540.0;
        const float white_min_g = 535.0, white_max_g = 555.0;
        const float white_min_b = 535.0, white_max_b = 565.0;

        const float yellow_min_r = 445.0, yellow_max_r = 465.0;
        const float yellow_min_g = 360.0, yellow_max_g = 375.0;
        const float yellow_min_b = 240.0, yellow_max_b = 260.0;


        //const float white_min_value = 200.0;
        //const float black_max_value = 50.0;

        // Determine the color based on HSV values
        std::cerr << ">>> Measurement : " << measuredColor << std::endl;

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

        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
}

int main() {
    // Get a reference to the drive
    auto drive = Drive::getInstance();
    std::thread thread(colorThread);

    // Wait for ten seconds
    std::this_thread::sleep_for(std::chrono::milliseconds{10000});

    // Stop the drive
    drive.coast();
    thread.join();

    return 0;
}

*/

// test code************************************+++
// test code************************************+++
// test code************************************+++

// test code************************************+++
// test code************************************+++
// test code************************************+++
// test code************************************+++
// test code************************************+++
// test code************************************+++
// test code************************************+++


#include <thread>
#include <iostream>
#include <chrono>
#include "functions/Drive.hpp"
#include "modules/sensors/ColorSensor.hpp"

void colorThread() {
    ColorSensor colorSensor;
    for (int i = 0; i < 10; i++) {
        auto measuredColor = colorSensor.get_color();
        
        float r = measuredColor.hue;  // These should be the RGB values
        float g = measuredColor.sat;  // These should be the RGB values
        float b = measuredColor.val;  // These should be the RGB values

        std::string colorName;

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

        const float white_min_r = 200.0, white_max_r = 255.0;
        const float white_min_g = 200.0, white_max_g = 255.0;
        const float white_min_b = 200.0, white_max_b = 255.0;

        const float yellow_min_r = 200.0, yellow_max_r = 255.0;
        const float yellow_min_g = 200.0, yellow_max_g = 255.0;
        const float yellow_min_b = 0.0, yellow_max_b = 100.0;

        // Determine the color based on RGB values
        std::cerr << ">>> Measurement (r|g|b) : " << measuredColor << std::endl;

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

        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
}

int main() {
    // Get a reference to the drive
    auto drive = Drive::getInstance();
    std::thread thread(colorThread);

    // Wait for ten seconds
    std::this_thread::sleep_for(std::chrono::milliseconds{10000});

    // Stop the drive
    drive.coast();
    thread.join();

    return 0;
}
