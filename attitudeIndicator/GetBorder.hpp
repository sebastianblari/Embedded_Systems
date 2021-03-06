/*
 * Task: GetBorder
 *
 * GetBorder.hpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastián
 */


#ifndef GETBORDER_HPP_
#define GETBORDER_HPP_

#include "math.h"
#include "Task.hpp"

#define __NOP __nop
#define PIXELS 129 //cantidad de pixeles

/* Class: GetBorder
 * inherit from Class Task
 */
class GetBorder : public Task
{
    public:
        GetBorder(); //constructor
        int m_iXYCoordinates[PIXELS];
        virtual uint8_t run(void);
        virtual uint8_t setup(Mailbox *i_pMailboxPtr);
        uint8_t BuildMsgData(void);
        int* DecodeMsgData(void);

    protected:
    private:
};

#endif /* GETBORDER_HPP_ */
