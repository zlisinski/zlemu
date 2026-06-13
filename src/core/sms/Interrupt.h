#ifndef ZLEMU_CORE_SMS_INTERRUPT_H
#define ZLEMU_CORE_SMS_INTERRUPT_H

namespace Sms
{


class Interrupt
{
public:
    void RequestInterrupt() {isIrq = true;}
    void ClearInterrupt() {isIrq = false;}
    bool CheckInterrupt() const {return isIrq;}

protected:
    bool isIrq = false;
};


}

#endif
