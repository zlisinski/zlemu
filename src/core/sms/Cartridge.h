#ifndef ZLEMU_CORE_SMS_CARTRIDGE_H
#define ZLEMU_CORE_SMS_CARTRIDGE_H

#include <vector>
#include <core/Zlemu.h>


namespace Sms
{


class Cartridge
{
public:
    enum class ERegion : uint8_t
    {
        Unknown = 0,
        SmsJapan = 3,
        SmsExport = 4,
        GgJapan = 5,
        GgExport = 6,
        GgInternational = 7,
    };

    bool Load(std::vector<uint8_t> romData);
    void Reset();

    bool IsLoaded() const {return isLoaded;}

    const std::vector<uint8_t> &GetRom() const {return rom;}
    ERegion GetRegion() const {return region;}

protected:
    std::vector<uint8_t> rom;
    bool isLoaded = false;
    ERegion region = ERegion::Unknown;
};


}

#endif
