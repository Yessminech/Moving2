#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cassert>

bool STATUS_RUNNING = true;
bool save_data = false;

std::string colorName;
std::string distanceRange;
std::string lastcolor;
std::string lastdistance;
std::string prev_col;
std::string prev_dist;

struct Color {
    float hue;
    float sat;
    float val;
};

struct MockColorSensor {
    virtual Color get_color() = 0;
    virtual ~MockColorSensor() = default;
};

struct MockColorSensor_default : MockColorSensor {
    Color get_color() override {
        return {200.0, 250.0, 300.0};
    }
};

struct MockColorSensor_white : MockColorSensor {
    Color get_color() override {
        return {550.0, 550.0, 570.0};
    }
};

struct MockDistanceSensor {
    virtual float get_distance() = 0;
    virtual ~MockDistanceSensor() = default;
};

struct MockDistanceSensor_default : MockDistanceSensor {
    float get_distance() override {
        return 600.0;
    }
};

struct MockDistanceSensor_out : MockDistanceSensor {
    float get_distance() override {
        return 1201.0;
    }
};

std::unique_ptr<MockColorSensor> colorSensor;
std::unique_ptr<MockDistanceSensor> distanceSensor;

Color measuredColor;
float measuredDistance;

void getSensorreading() {
    while (STATUS_RUNNING) {
        measuredColor = colorSensor->get_color();
        float r = measuredColor.hue;
        float g = measuredColor.sat;
        float b = measuredColor.val;

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
        }

        std::cout << "Detected Color: " << colorName << std::endl;

        measuredDistance = distanceSensor->get_distance();
        std::cerr << ">>> Measurement Distance : " << measuredDistance << std::endl;

        if (0 < measuredDistance && measuredDistance <= 240) {
            distanceRange = "dist_4";
        } else if (241 <= measuredDistance && measuredDistance <= 480) {
            distanceRange = "dist_3";
        } else if (481 <= measuredDistance && measuredDistance <= 720) {
            distanceRange = "dist_2";
        } else if (721 <= measuredDistance && measuredDistance <= 960) {
            distanceRange = "dist_1";
        } else if (961 <= measuredDistance && measuredDistance <= 1200) {
            distanceRange = "dist_0";
        } else if (measuredDistance == -1) {
            distanceRange = "dist_out";
        } else if (measuredDistance > 1200) {
            distanceRange = "dist_out";
        } else {
            distanceRange = "dist_out";
        }

        std::cout << "Distance Range: " << distanceRange << std::endl;
        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds{1000});

        if (save_data) {
            prev_col = lastcolor;
            prev_dist = lastdistance;
            save_data = false;
        }
        lastdistance = distanceRange;
        lastcolor = colorName;

        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
}

// Test case for getSensorreading
void test_getSensorreading() {
    // Test 1: General test with mock color (blue) and distance (dist_2)
    {
        // Initialize mock sensor data
        colorSensor = std::make_unique<MockColorSensor_default>();
        distanceSensor = std::make_unique<MockDistanceSensor_default>();
        STATUS_RUNNING = true;

        // Start the getSensorreading function in a separate thread
        std::thread sensorThread(getSensorreading);

        // Let it run for a short while and then stop it
        std::this_thread::sleep_for(std::chrono::seconds(3));
        STATUS_RUNNING = false;

        // Wait for the thread to finish
        sensorThread.join();

        // Validate the outputs
        assert(colorName == "blue");
        assert(distanceRange == "dist_2");

        std::cout << "Test 1: General test passed!" << std::endl;
    }

    // Test 2: Distance out and color white
    {
        // Initialize mock sensor data
        colorSensor = std::make_unique<MockColorSensor_white>();
        distanceSensor = std::make_unique<MockDistanceSensor_out>();
        STATUS_RUNNING = true;

        // Start the getSensorreading function in a separate thread
        std::thread sensorThread(getSensorreading);

        // Let it run for a short while and then stop it
        std::this_thread::sleep_for(std::chrono::seconds(3));
        STATUS_RUNNING = false;

        // Wait for the thread to finish
        sensorThread.join();

        // Validate the outputs
        assert(colorName == "white");
        assert(distanceRange == "dist_out");

        std::cout << "Test 2: White color and default distance passed!" << std::endl;
    }
}

int main() {
    test_getSensorreading();

    return 0;
}