#include <fstream>
#include <vector>

#include <core/Logger.h>
#include "Bus.h"
#include "Emulator.h"
#include "Input.h"
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

    input = new Input();
    interrupt = new Interrupt();
    vdp = new Vdp(interrupt, displayInterface);
    memory = new Memory();
    bus = new Bus(input, memory, vdp);
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


void Emulator::ButtonPressed(Buttons::Button button)
{
    uint8_t oldButtonData = buttons.data;
    buttons.data |= button;

    if (input && buttons.data != oldButtonData)
        input->SetButtons(buttons);
}


void Emulator::ButtonReleased(Buttons::Button button)
{
    uint8_t oldButtonData = buttons.data;
    buttons.data &= ~button;

    if (input && buttons.data != oldButtonData)
        input->SetButtons(buttons);
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

    delete bus;
    delete cpu;
    delete input;
    delete interrupt;
    delete memory;
    delete timer;
    delete vdp;
    bus = nullptr;
    cpu = nullptr;
    input = nullptr;
    interrupt = nullptr;
    memory = nullptr;
    timer = nullptr;
    vdp = nullptr;
}


}