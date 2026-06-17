#ifndef ZLEMU_CORE_SMS_EMULATOR_H
#define ZLEMU_CORE_SMS_EMULATOR_H

#include <string_view>
#include <thread>

#include <core/AbsEmulator.h>


class DisplayInterface;

namespace Sms
{

class Bus;
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

    bool LoadRom(std::string_view filename) override;
    void EndEmulation() override;
    void Reset() override {}
    void Pause() override {}

protected:
    void ThreadFunc();

    volatile bool paused = false;
    volatile bool quit = false;

    std::thread workThread;

    Bus *bus = nullptr;
    Interrupt *interrupt = nullptr;
    Memory *memory = nullptr;
    Timer *timer = nullptr;
    Vdp *vdp = nullptr;
    Z80 *cpu = nullptr;

    DisplayInterface *displayInterface = nullptr;
};


}

#endif
