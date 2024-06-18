#include <thread>
#include "functions/Drive.hpp"

int main() {
    // get a reference to the drive
    auto drive = Drive::getInstance();

    // drive forward for one second with 50% speed
    drive.set_speed(0.5);
    drive.move_forward(0);

    // wait for one second
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    // stop the drive
    drive.coast();

    return 0;
}