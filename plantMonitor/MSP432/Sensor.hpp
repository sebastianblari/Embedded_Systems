/*
 * Sensor.hpp
 *
 *      Author: Laura,Sebastián,Dunia
 */

#ifndef SENSOR_HPP_
#define SENSOR_HPP_

 #include <ti/devices/msp432p4xx/inc/msp.h>

#define NO_ERR 0
#define RET_ERR 1

template <typename numType>

class Sensor
{
    public:
        Sensor();
        bool sensorStatus;
        uint8_t m_u8SensorID;
        virtual numType GetValue(void) = 0;
        virtual uint8_t setup(void) = 0;
        virtual uint8_t EnableSensor(void) = 0;
        virtual uint8_t DisableSensor(void) = 0;
    private:
        static uint8_t m_u8NextSensorID;
};

template <typename numType>
Sensor<numType>::Sensor()
{
    m_u8SensorID = m_u8NextSensorID; //assign id
    m_u8NextSensorID++;
}


#endif /* SENSOR_HPP_ */
