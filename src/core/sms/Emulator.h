#ifndef ZLEMU_CORE_SMS_EMULATOR_H
#define ZLEMU_CORE_SMS_EMULATOR_H

#include <string_view>
#include <thread>

#include <core/AbsEmulator.h>


namespace Sms
{

class Interrupt;
class Memory;
class Timer;
class Vdp;
class Z80;


class Emulator : public AbsEmulator
{
public:
    Emulator();
    ~Emulator() override;

    bool LoadRom(std::string_view filename) override;
    void EndEmulation() override;

protected:
    void ThreadFunc();

    bool paused = false;
    bool quit = false;

    std::thread workThread;

    Interrupt *interrupt = nullptr;
    Memory *memory = nullptr;
    Timer *timer = nullptr;
    Vdp *vdp = nullptr;
    Z80 *cpu = nullptr;
};


}

#endif
