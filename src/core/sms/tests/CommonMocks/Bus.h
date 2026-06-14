#ifndef ZLEMU_CORE_SMS_BUS_H
#define ZLEMU_CORE_SMS_BUS_H

#include <array>
#include <core/Zlemu.h>


namespace Sms
{

class Memory;
class Vdp;


class Bus
{
public:
    Bus(Memory *memory, Vdp *vdp);

    uint8_t ReadPort(uint8_t port) const;
    void WritePort(uint8_t port, uint8_t value);

protected:
    std::array<uint8_t, 256> portData;
};


}

#endif
