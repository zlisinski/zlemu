#ifndef ZLEMU_CORE_SMS_EMULATOR_H
#define ZLEMU_CORE_SMS_EMULATOR_H

#include <thread>

#include <core/AbsEmulator.h>
#include <core/Buttons.h>
#include <core/Region.h>
#include "Cartridge.h"


class DisplayInterface;

namespace Sms
{

class Bus;
class Input;
class Interrupt;
class Memory;
class Timer;
class Vdp;
class Z80;


class Emulator : public AbsEmulator
{
public:
    Emulator(DisplayInterface *displayInterface);
    ~Emulator() override;

    void SetBios(std::vector<uint8_t> data) override;
    void SetRom(std::vector<uint8_t> data) override;
    void SetRegion(ERegion region) override {this->region = region;}
    bool StartEmulation() override;
    void EndEmulation() override;
    void Reset() override {}
    void Pause(bool pause) override {paused = pause;}
    void ButtonPressed(Buttons::Button button) override;
    void ButtonReleased(Buttons::Button button) override;

protected:
    void ThreadFunc();
    bool IsJapanese() const;

    volatile bool paused = false;
    volatile bool quit = false;

    std::thread workThread;

    std::vector<uint8_t> bios;
    Cartridge cartridge;

    Bus *bus = nullptr;
    Buttons buttons;
    Input *input = nullptr;
    Interrupt *interrupt = nullptr;
    Memory *memory = nullptr;
    Timer *timer = nullptr;
    Vdp *vdp = nullptr;
    Z80 *cpu = nullptr;

    DisplayInterface *displayInterface = nullptr;

    ERegion region = ERegion::AutoDetect;
};


}

#endif
