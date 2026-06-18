#ifndef ZLEMU_CORE_ABSEMULATOR_H
#define ZLEMU_CORE_ABSEMULATOR_H


#include <string_view>


class AbsEmulator
{
public:
    virtual ~AbsEmulator() = default;

    virtual void SetBios(std::vector<uint8_t> data) = 0;
    virtual void SetRom(std::vector<uint8_t> data) = 0;
    virtual bool StartEmulation() = 0;
    virtual void EndEmulation() = 0;
    virtual void Reset() = 0;
    virtual void Pause() = 0;
};


#endif