#include <thread>
#include <cstdlib>
#include "functions/Drive.hpp"
#include "modules/sensors/DistanceSensor.hpp"

void colorThread(){
    DistanceSensor distanceSensor;
    for (int i = 0; i < 10; i++)
    {        
        int measuredDistance = distanceSensor.get_distance();
        std::cerr << ">>> Measurement : " << measuredDistance << std::endl;        
        std::cout << std::endl;
        std::cout << std::endl;
    }
    
}

int main() {
    // get a reference to the drive
    auto drive = Drive::getInstance();
    std::thread thread(colorThread);

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