#ifndef ZLEMU_CORE_SMS_INTERRUPT_H
#define ZLEMU_CORE_SMS_INTERRUPT_H

namespace Sms
{


class Interrupt
{
public:
    void RequestIrq() {isIrq = true;}
    void ClearIrq() {isIrq = false;}
    bool IsIrq() const {return isIrq;}

    void RequestNmi() {isNmi = true;}
    void ClearNmi() {isNmi = false;}
    bool IsNmi() const {return isNmi;}

    bool CheckInterrupt() const {return isIrq || isNmi;}

protected:
    bool isIrq = false;
    bool isNmi = false;
};


}

#endif
