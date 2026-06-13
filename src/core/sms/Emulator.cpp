#include <fstream>
#include <vector>

#include <core/Logger.h>
#include "Emulator.h"
#include "Interrupt.h"
#include "Memory.h"
#include "Timer.h"
#include "Vdp.h"
#include "Z80.h"


namespace Sms
{


Emulator::Emulator()
{
}


Emulator::~Emulator()
{
    Emulator::EndEmulation();
}


bool Emulator::LoadRom(std::string_view filename)
{
    std::ifstream file(filename.data(), std::ios::binary);
    if (!file)
    {
        LogError("Unable to open file %s", filename.data());
        return false;
    }
    std::istreambuf_iterator<char> start(file), end;
    std::vector<uint8_t> data(start, end);

    memory = new Memory();
    interrupt = new Interrupt();
    vdp = new Vdp();
    timer = new Timer(interrupt, vdp);
    cpu = new Z80(memory, timer, interrupt);

    memory->SetBios(std::move(data));

    workThread = std::thread(&Emulator::ThreadFunc, this);

    return true;
}


void Emulator::EndEmulation()
{
    if (workThread.joinable())
    {
        quit = true;
        workThread.join();
    }
}


void Emulator::ThreadFunc()
{
    try
    {
        while (!quit)
        {
            cpu->ProcessOpcode();
        }
    }
    catch (const std::exception &e)
    {
        LogError(e.what());
    }

    delete cpu;
    delete vdp;
    delete interrupt;
    delete timer;
    delete memory;
    cpu = nullptr;
    interrupt = nullptr;
    memory = nullptr;
    timer = nullptr;
    vdp = nullptr;
}


}