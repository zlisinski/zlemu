#ifndef ZLEMU_CORE_DISPLAYINTERFACE_H
#define ZLEMU_CORE_DISPLAYINTERFACE_H

#include <array>
#include <string>

#include "Zlemu.h"


class DisplayInterface
{
public:
    virtual ~DisplayInterface() = default;
    virtual void FrameReady(const std::array<uint32_t, 256 * 240> &frameBuffer) = 0;
    virtual void RequestMessageBox(const std::string &message) = 0;
};

#endif