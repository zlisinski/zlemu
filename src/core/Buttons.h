#ifndef ZLEMU_CORE_BUTTONS_H
#define ZLEMU_CORE_BUTTONS_H

#include "Zlemu.h"


class Buttons
{
public:
    enum Button
    {
        eButtonNone = 0x00,
        eButtonUp = 0x01,
        eButtonDown = 0x02,
        eButtonLeft = 0x04,
        eButtonRight = 0x08,
        eButton1 = 0x10,
        eButton2 = 0x20,
        eButtonPause = 0x40,
    };

    Buttons() : data(0) {}

    bool IsUpPressed() const {return data & eButtonUp;}
    bool IsDownPressed() const {return data & eButtonDown;}
    bool IsLeftPressed() const {return data & eButtonLeft;}
    bool IsRightPressed() const {return data & eButtonRight;}
    bool IsButton1Pressed() const {return data & eButton1;}
    bool IsButton2Pressed() const {return data & eButton2;}
    bool IsPausePressed() const {return data & eButtonPause;}

    void SetButton(Button button) {data |= button;}
    void ClearButton(Button button) {data &= ~button;}

    bool operator==(const Buttons &other) const {return data == other.data;}

    uint8_t data;
};

#endif
