#ifndef MODULES_SENSORS_DISTANCESENSOR_HPP
#define MODULES_SENSORS_DISTANCESENSOR_HPP

#include <cstdint>

#include "config.hpp"

#include "BuildHat.hpp"

/**
 * @brief abstraction for color sensor access
 * remember to calibrate the sensor before use and retrieve the calibration file for later use
 *
 */
class DistanceSensor {
public:
    explicit DistanceSensor(uint8_t port = PORT_DISTANCE_SENSOR);
    ~DistanceSensor();


    /**
     * @brief get the color of the object in front of the sensor
     *
     * @return Color
     */
    int get_distance();

private:
    bool available = false;
    uint8_t port{};

    BuildHat &buildHat = BuildHat::getInstance();
};

#endif //MODULES_SENSORS_DISTANCESENSOR_HPP
