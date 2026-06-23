#include "Input.h"

#include <core/Bytes.h>


namespace Sms
{


Input::Input()
{

}


void Input::SetIoControlRegister(uint8_t value)
{
    ioControlRegister = value;
}


uint8_t Input::ReadPort1() const
{
    if (!isEnabled)
        return 0xFF;

    uint8_t value = ~(buttons.data & 0x3F);

    return value;
}


uint8_t Input::ReadPort2() const
{
    if (!isEnabled)
        return 0xFF;
    return 0xFF;
}


}
