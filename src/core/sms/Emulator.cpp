#include <fstream>
#include <vector>

#include <core/Logger.h>
#include "Bus.h"
#include "Emulator.h"
#include "Interrupt.h"
#include "Memory.h"
#include "Timer.h"
#include "Vdp.h"
#include "Z80.h"


namespace Sms
{


Emulator::Emulator(DisplayInterface *displayInterface) :
    displayInterface(displayInterface)
{
}


Emulator::~Emulator()
{
    Emulator::EndEmulation();
}


void Emulator::SetBios(std::vector<uint8_t> data)
{
    bios = std::move(data);
}


void Emulator::SetRom(std::vector<uint8_t> data)
{
    rom = std::move(data);
}


bool Emulator::StartEmulation()
{
    if (rom.empty())
    {
        LogError("No ROM loaded");
        return false;
    }

    EndEmulation();

    interrupt = new Interrupt();
    vdp = new Vdp(interrupt, displayInterface);
    memory = new Memory();
    bus = new Bus(memory, vdp);
    timer = new Timer(vdp);
    cpu = new Z80(bus, memory, timer, interrupt);

    if (!bios.empty())
        memory->SetBios(bios);
    memory->SetRom(rom);
    memory->Reset();

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
    quit = false;

    try
    {
        while (!quit)
        {
            if (!paused)
                cpu->Cycle();
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
    delete bus;
    cpu = nullptr;
    interrupt = nullptr;
    memory = nullptr;
    timer = nullptr;
    vdp = nullptr;
    bus = nullptr;
}


}