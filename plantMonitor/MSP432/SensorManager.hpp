/*
 * SensorManager.hpp
 *
 */

#ifndef SENSORMANAGER_HPP_
#define SENSORMANAGER_HPP_

#include "Sensor.hpp"

#define NUMBER_OF_SENSORS 255
#define NO_ERR 0

//-------------------------------------------------------
// This structure defines the Sensor Information
template <typename numType>
struct st_SensorInfo {
    Sensor<numType> * pToAttach; //pointer to the Sensor
};

//-------------------------------------------------------


template <typename numType>
class SensorManager
{
   public:
       SensorManager();
       uint64_t m_u64ticks;
       uint8_t attach(Sensor<numType> * i_Toattach);
       uint8_t run(void);
       uint8_t setup(void);
       uint8_t remove(Sensor<numType> * i_ToRemove);
       uint8_t ManageRequest(uint16_t i_Request);
   private:
       uint8_t m_u8OpenSlots; // Available slots
       uint8_t m_u8NextSlot;  // Next available slot
       st_SensorInfo<numType> m_aSensors[NUMBER_OF_SENSORS]; // Current sensors to be executed

};

//-------------------------------------------------------
// Sensor manager constructor
template <typename numType>
SensorManager<numType>::SensorManager()
{
    m_u8OpenSlots = static_cast<uint8_t>(NUMBER_OF_SENSORS);
    m_u8NextSlot = 0;
    for(int index = 0; index < NUMBER_OF_SENSORS; index++)
    {
        m_aSensors[index].pToAttach = (uintptr_t) 0; // Init to an invalid pointer
    }
    return;
}

//-------------------------------------------------------
// The attach function, saves their pointer into the array..
template <typename numType>
uint8_t SensorManager<numType>::attach(Sensor<numType>* i_Toattach){
    uint8_t l_ErrorCode = NO_ERR;
    st_SensorInfo<numType> l_st_StructToAttach;

    l_st_StructToAttach.pToAttach = i_Toattach;

    if((m_u8OpenSlots>0) && (m_u8NextSlot < NUMBER_OF_SENSORS))
    {
        m_aSensors[m_u8NextSlot] =  l_st_StructToAttach;
        m_u8OpenSlots--;
        m_u8NextSlot++;
    }
    else
    {
        l_ErrorCode = RET_ERR;
    }
    return l_ErrorCode;
}
//-------------------------------------------------------
// The remove function, change the status of a specific sensor.
template <typename numType>
uint8_t SensorManager<numType>::remove(Sensor<numType> * i_ToRemove)
{
    i_ToRemove->DisableSensor();

    return NO_ERR;
}
//-------------------------------------------------------
// Execute the current active sensors
template <typename numType>
uint8_t SensorManager<numType>::run(void)
{
    int l_iNextSensorSlot = 0U;
    Sensor<numType>* l_pNextSensor = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;

    while(l_iNextSensorSlot < NUMBER_OF_SENSORS)
    {
        l_pNextSensor = static_cast<Sensor<numType> *> (m_aSensors[l_iNextSensorSlot].pToAttach);
        if(l_pNextSensor != ((uintptr_t) 0))
        {
                l_pNextSensor->GetValue();
        }
        l_iNextSensorSlot++;
    }
    printf(EUSCI_A0_BASE, ".");

    return l_u8ReturnCode;
}

//-------------------------------------------------------
// Execute the setup function for all sensors
template <typename numType>
uint8_t SensorManager<numType>::setup()
{
    int l_iNextSensorSlot = 0U;
    Sensor<numType> * l_pNextSensor = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;

    while(l_iNextSensorSlot < NUMBER_OF_SENSORS)
    {
        l_pNextSensor = static_cast<Sensor<numType> *> (m_aSensors[l_iNextSensorSlot].pToAttach);
        if(l_pNextSensor != ((uintptr_t) 0))
        {
            l_pNextSensor->setup();
        }
        l_iNextSensorSlot++;
    }
    return l_u8ReturnCode;
}

//-------------------------------------------------------
// Identifies the sensor manager request action
template <typename numType>
uint8_t SensorManager<numType>::ManageRequest(uint16_t i_Request){
   // i_Request =  OP0 OP1 ID1 ID0

   /* Identify the Sensor<numType>ID requested
    * by applying a mask
    */
   uint16_t l_u16IDmask = 0x11;

   l_u16IDmask &= i_Request;

   /* Identify the operation required
    * by applying a mask
    * 0x11 - Activated SensorID
    * 0x00 - Turn off SensorID
   */
   uint16_t l_u16RequestMask = 0x1100;

   l_u16RequestMask &= i_Request;
   l_u16RequestMask = l_u16RequestMask >> 8;


   int l_iNextSensorSlot = 0U;
   Sensor<numType> * l_pNextSensor = (uintptr_t) 0;

// Activate --------------------------------------------------------
   if (l_u16RequestMask == 0x11){


       while(l_iNextSensorSlot < NUMBER_OF_SENSORS)
       {
           l_pNextSensor = static_cast<Sensor<numType> *> (m_aSensors[l_iNextSensorSlot].pToAttach);
           if(l_pNextSensor != ((uintptr_t) 0) && l_pNextSensor->m_u8SensorID == l_u16IDmask)
           {
               l_pNextSensor->EnableSensor();
           }
           l_iNextSensorSlot++;
       }

   }
// Disable ---------------------------------------------------------
   else if(l_u16RequestMask == 0){
       while(l_iNextSensorSlot < NUMBER_OF_SENSORS)
       {
           l_pNextSensor = static_cast<Sensor<numType> *> (m_aSensors[l_iNextSensorSlot].pToAttach);
           if(l_pNextSensor != ((uintptr_t) 0) && l_pNextSensor->m_u8SensorID == l_u16IDmask)
           {
               l_pNextSensor->DisableSensor();
           }
           l_iNextSensorSlot++;
       }

   }

// Lectures -----------------------------------------------------
   else if(l_u16RequestMask == 0x10 && l_u16RequestMask == 0x10){
       this->run();
   }
    return NO_ERR;

   }

#endif /* SENSORMANAGER_HPP_ */
