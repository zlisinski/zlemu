#ifndef ZLEMU_CORE_SMS_BUS_H
#define ZLEMU_CORE_SMS_BUS_H

#include <core/Zlemu.h>


namespace Sms
{

class Input;
class Memory;
class Vdp;


class Bus
{
public:
    Bus(Input *input, Memory *memory, Vdp *vdp);

    uint8_t ReadPort(uint8_t port) const;
    void WritePort(uint8_t port, uint8_t value);

protected:
    Input *input = nullptr;
    Memory *memory = nullptr;
    Vdp *vdp = nullptr;
};


}

#endif
