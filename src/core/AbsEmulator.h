#ifndef ZLEMU_CORE_ABSEMULATOR_H
#define ZLEMU_CORE_ABSEMULATOR_H


#include "Buttons.h"
#include "Region.h"


class AbsEmulator
{
public:
    virtual ~AbsEmulator() = default;

    virtual void SetBios(std::vector<uint8_t> data) = 0;
    virtual void SetRom(std::vector<uint8_t> data) = 0;
    virtual void SetRegion(ERegion region) = 0;
    virtual bool StartEmulation() = 0;
    virtual void EndEmulation() = 0;
    virtual void Reset() = 0;
    virtual void Pause(bool pause) = 0;
    virtual void ButtonPressed(Buttons::Button button) = 0;
    virtual void ButtonReleased(Buttons::Button button) = 0;
};


#endif