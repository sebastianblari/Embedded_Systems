/*
 * Sensor.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#ifndef SENSOR_HPP_
#define SENSOR_HPP_

#include <ti/devices/msp432p4xx/inc/msp.h>

#define NO_ERR 0
#define RET_ERR 1

//template <typename numType>

class Sensor
{
    public:
        Sensor();
        uint8_t m_u8SensorID;
//        virtual numType GetValue(void);
        virtual uint16_t GetValue(void) =0;
        virtual uint8_t setup(void) =0;
        virtual uint8_t EnableSensor(void)=0;
        virtual uint8_t DisableSensor(void)=0;
    private:
        static uint8_t m_u8NextSensorID;
};



#endif /* SENSOR_HPP_ */
