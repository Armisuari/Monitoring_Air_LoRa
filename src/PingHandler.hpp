#pragma once

class PingHandler
{
public:
    PingHandler(uint8_t trig, uint8_t echo);
    uint32_t getDistance();

private:
    uint8_t _trig, _echo;
    unsigned long duration, pembacaan;
    void triggerSensor(); // new private method added to trigger the sensor
};

PingHandler::PingHandler(uint8_t trig, uint8_t echo) // constructor modified to set pinMode for both trig and echo pins
{                                                    // and assign them to the class variables.

    pinMode(trig, OUTPUT); // set trig pin as output
    pinMode(echo, INPUT);  // set echo pin as input

    _trig = trig; // assign trig and echo pins to class variables
    _echo = echo;
}

// new method added to trigger the sensor. This is a private method as it is only used within this class.

void PingHandler::triggerSensor()
{

    digitalWrite(_trig, LOW); // set the trigger pin low for 5 microseconds
    delayMicroseconds(2);

    digitalWrite(_trig, HIGH); // set the trigger pin high for 10 microseconds
    delayMicroseconds(20);

    digitalWrite(_trig, LOW); // set the trigger pin low again
}

uint32_t PingHandler::getDistance()
{ // modified method name from distance() to getDistance() for clarity.

    triggerSensor(); // call private method to trigger sensor before taking measurement.

    duration = pulseIn(_echo, HIGH); // measure duration of return pulse from sensor.
    uint32_t pembacaan = duration * 0.034 / 2;
    uint32_t jarak = (pembacaan + 0.6035) / 0.9639;

    return 81 - jarak; // calculate distance from duration and return it.
}