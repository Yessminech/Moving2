#include <thread>
#include <iostream>
#include <chrono>
#include "functions/Drive.hpp"
#include "modules/sensors/ColorSensor.hpp"

// Scale a value from one range to another
float scaleValue(float value, float oldMin, float oldMax, float newMin, float newMax) {
    return ((value - oldMin) * (newMax - newMin) / (oldMax - oldMin)) + newMin;
}

void colorThread() {
    ColorSensor colorSensor;
    for (int i = 0; i < 10; i++) {
        auto measuredColor = colorSensor.get_color();
        
        // Normalize the hue value if it exceeds 360 degrees
        float normalizedHue = measuredColor.hue;
        if (normalizedHue > 360.0) {
            normalizedHue -= 360.0;
        }
        
        // Scale down the saturation and value components to fit within the specified range
        float scaledSaturation = scaleValue(measuredColor.sat, 0.0, 100.0, 0.0, 250.0);
        float scaledValue = scaleValue(measuredColor.val, 0.0, 100.0, 0.0, 250.0);

        // Print the measured hue, saturation, and value
        std::cout << ">>> Measurement : {hue: " << normalizedHue
                  << ", sat: " << scaledSaturation
                  << ", val: " << scaledValue << "}" << std::endl;

        std::string colorName;

        // Define ranges for each color
        const float red_min_hue = 0.0, red_max_hue = 20.0;
        const float yellow_min_hue = 60.0, yellow_max_hue = 120.0; // Adjusted for yellow
        const float blue_min_hue = 200.0, blue_max_hue = 250.0;
        const float white_min_value = 200.0;
        const float black_max_value = 50.0;

        // Determine the color based on HSV values
        if (scaledValue < black_max_value) {
            colorName = "Black";
        } else if (scaledValue > white_min_value) {
            colorName = "White";
        } else if (normalizedHue >= red_min_hue && normalizedHue <= red_max_hue) {
            colorName = "Red";
        } else if (normalizedHue >= yellow_min_hue && normalizedHue <= yellow_max_hue &&
                   scaledSaturation > 50 && scaledValue > 50) { // Adjusted for yellow
            colorName = "Yellow";
        } else if (normalizedHue >= blue_min_hue && normalizedHue <= blue_max_hue) {
            colorName = "Blue";
        } else {
            colorName = "Unknown";
        }

        // Print the detected color
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
