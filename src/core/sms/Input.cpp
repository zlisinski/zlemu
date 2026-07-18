#include "Input.h"

#include <core/Bytes.h>
#include <core/Logger.h>


namespace Sms
{


Input::Input(bool isJapanese) :
    isJapanese(isJapanese)
{

}


void Input::SetIoControlRegister(uint8_t value)
{
    ioControlRegister = value;
    thBLevel = Bytes::GetBit<7>(value);
    trBLevel = Bytes::GetBit<6>(value);
    thALevel = Bytes::GetBit<5>(value);
    trALevel = Bytes::GetBit<4>(value);
    thBInput = Bytes::GetBit<3>(value);
    trBInput = Bytes::GetBit<2>(value);
    thAInput = Bytes::GetBit<1>(value);
    trAInput = Bytes::GetBit<0>(value);

    const char *level[] = {"Low", "High"};
    const char *dir[] = {"Out", "In"};
    LogInput("IoControlRegister=%02X BTH=%s BTR=%s ATH=%s ATR=%s BTH=%s BTR=%s ATH=%s ATR=%s", ioControlRegister,
             level[thBLevel], level[trBLevel], level[thALevel], level[trALevel],
             dir[thBInput], dir[trBInput], dir[thAInput], dir[trAInput]);
}


uint8_t Input::ReadPort1() const
{
    if (!isEnabled)
    {
        LogInput("ReadPort1 port not enabled");
        return 0xFF;
    }

    uint8_t value = ~(buttons.data & 0x3F);

    LogInput("ReadPort1 = %02X", value);
    return value;
}


uint8_t Input::ReadPort2() const
{
    if (!isEnabled)
        return 0xFF;

    uint8_t value = 0xFF;

    if (!thBInput)
    {
        Bytes::ClearBit<7>(value);
        if (!isJapanese && thBLevel)
            Bytes::SetBit<7>(value);
    }

    if (!thAInput)
    {
        Bytes::ClearBit<6>(value);
        if (!isJapanese && thALevel)
            Bytes::SetBit<6>(value);
    }

    LogInput("ReadPort2 = %02X", value);
    return value;
}


}
