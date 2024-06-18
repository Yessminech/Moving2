#include "DistanceSensor.hpp"

#include <array>
#include <cmath>
#include <thread>
#include <sstream>


DistanceSensor::DistanceSensor(uint8_t port) {
    if (port > 3) {
        std::cerr << "DistanceSensor: port must be between 0 and 3" << std::endl;
        return;
    }

    this->port = port;

    // sometimes the sensor gets stuck in an off mode but doesn't know it, so we explicitly turn it off
    buildHat.serial_write_line("port " + std::to_string(this->port) + " ; set 0", false);

    // and only then turn it on
    buildHat.serial_write_line("port " + std::to_string(this->port) + " ; set -1", false);

    this->available = true;
}

DistanceSensor::~DistanceSensor() {
    // turn off the sensor
    buildHat.serial_write_line("port " + std::to_string(this->port) + " ; set 0", false);
}


int DistanceSensor::get_distance() {
    if (!available) {
        std::cerr << "DistanceSensor: not available" << std::endl;
        return {};
    }

    // read data
    auto data = buildHat.serial_write_read("port " + std::to_string(this->port) + " ; selonce 0");

    if (data.length() < 2) {
        std::cerr << "DistanceSensor: not available: " << data << std::endl;
        return {};
    }

    // strip prefix
    data = data.substr(6);

    // parse data
    std::istringstream iss(data);
    int distance;
    iss >> distance;

    if (distance == -1) {
        std::cerr << "Got no distance" << std::endl;
        return {};
    }

    // decode data
    //distance = static_cast<long>((distance / 1024.0) * 100);

    return distance;
}

