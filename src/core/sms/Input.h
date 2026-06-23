#ifndef ZLEMU_CORE_SMS_INPUT_H
#define ZLEMU_CORE_SMS_INPUT_H

#include <core/Buttons.h>
#include <core/Zlemu.h>


namespace Sms
{


class Input
{
public:
    Input();

    void SetButtons(const Buttons &buttons) {this->buttons = buttons;}
    void SetEnabled(bool enabled) {isEnabled = enabled;}
    void SetIoControlRegister(uint8_t value);

    uint8_t ReadPort1() const;
    uint8_t ReadPort2() const;

protected:
    Buttons buttons;
    bool isEnabled = true;
    uint8_t ioControlRegister = 0;
};


}

#endif
