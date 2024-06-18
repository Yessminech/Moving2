#include "Motor.hpp"

// set to true to print motor commands to stdout
#define DEBUG_MOTOR_COMMANDS false

Motor::Motor(uint8_t id, bool inverted) {
    if (id > 3) {
        std::cerr << "Motor: id must be between 0 and 3" << std::endl;
        return;
    }

    this->id = id;
    this->inverted = inverted;

    // set pwm limit
    hat.serial_write_line("port " + std::to_string(this->id) + " ; plimit 1.0", DEBUG_MOTOR_COMMANDS);

    // set pwm params
    hat.serial_write_line("port " + std::to_string(this->id) + " ; pwmparams 0.0001 0.0001", DEBUG_MOTOR_COMMANDS);
}

void Motor::stop() {
    hat.serial_write_line("port " + std::to_string(id) + " ; off", DEBUG_MOTOR_COMMANDS);
}

void Motor::coast() {
    hat.serial_write_line("port " + std::to_string(id) + " ; coast", DEBUG_MOTOR_COMMANDS);
}

void Motor::set_speed(double speed) {
    if (inverted) speed = -speed;

    if (std::abs(speed) > 1.0) {
        std::cerr << "Motor: speed must be between -1.0 and 1.0" << std::endl;
        return;
    }

    hat.serial_write_line("port " + std::to_string(id) + " ; pwm ; set " + std::to_string(speed), DEBUG_MOTOR_COMMANDS);
}
