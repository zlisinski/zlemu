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
    cartridge.Load(std::move(data));
}


bool Emulator::StartEmulation()
{
    if (!cartridge.IsLoaded())
    {
        LogError("No ROM loaded");
        return false;
    }

    EndEmulation();

    interrupt = new Interrupt();
    vdp = new Vdp(interrupt, displayInterface);
    input = new Input(vdp, IsJapanese());
    memory = new Memory();
    bus = new Bus(input, memory, vdp);
    timer = new Timer(vdp);
    cpu = new Z80(bus, memory, timer, interrupt);

    if (!bios.empty())
        memory->SetBios(bios);
    memory->SetRom(cartridge.GetRom());
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
    Buttons oldButtons = buttons;
    buttons.SetButton(button);

    if (interrupt && buttons.IsPausePressed() && !oldButtons.IsPausePressed())
    {
        interrupt->RequestNmi();
        return;
    }

    if (input && buttons != oldButtons)
        input->SetButtons(buttons);
}


void Emulator::ButtonReleased(Buttons::Button button)
{
    Buttons oldButtons = buttons;
    buttons.ClearButton(button);

    if (input && buttons != oldButtons)
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


bool Emulator::IsJapanese() const
{
    switch (region)
    {
        case ERegion::AutoDetect:
            switch (cartridge.GetRegion())
            {
                case Cartridge::ERegion::SmsExport:
                case Cartridge::ERegion::GgExport:
                case Cartridge::ERegion::GgInternational:
                    return false;
                case Cartridge::ERegion::Unknown:
                case Cartridge::ERegion::SmsJapan:
                case Cartridge::ERegion::GgJapan:
                    return true;
            }
            break;
        case ERegion::Export:
            return false;
        case ERegion::Japan:
            return true;
    }

    return false;
}


}
