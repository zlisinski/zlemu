#include <string>
#include <unordered_map>

#include <core/Logger.h>

#include "Cartridge.h"


namespace Sms
{

constexpr size_t HeaderOffset = 0x7FF0;
constexpr size_t RegionOffset = 0x7FFF;
static const std::unordered_map<Cartridge::ERegion, std::string> RegionNames = {
    {Cartridge::ERegion::Unknown, "Unknown"},
    {Cartridge::ERegion::SmsJapan, "SMS Japan"},
    {Cartridge::ERegion::SmsExport, "SMS Export"},
    {Cartridge::ERegion::GgJapan, "GG Japan"},
    {Cartridge::ERegion::GgExport, "GG Export"},
    {Cartridge::ERegion::GgInternational, "GG International"},
};


bool Cartridge::Load(std::vector<uint8_t> romData)
{
    isLoaded = false;
    rom = std::move(romData);

    if (rom.size() < 0x8000)
    {
        LogError("Rom file is too small");
        rom.clear();
        return false;
    }

    // Detect copier header.
    size_t copierHeaderLen = rom.size() % 0x4000;
    if (copierHeaderLen != 0)
    {
        LogWarning("File size is not a multiple of 16KB");
        std::string tmr = "TMR SEGA";

        if (std::equal(tmr.cbegin(), tmr.cend(), rom.cbegin() + HeaderOffset))
        {
            LogWarning("Found header in correct location, stripping extra bytes off end of data");
            rom.resize(rom.size() - copierHeaderLen);
        }
        else
        {
            LogWarning("Stripping first %zu bytes", copierHeaderLen);
            rom.erase(rom.begin(), rom.begin() + copierHeaderLen);
            if (!std::equal(tmr.cbegin(), tmr.cend(), rom.cbegin() + HeaderOffset))
                LogWarning("No header found after stripping copier header from front on data, rom data possibly corrupted");
        }
    }

    int regionVal = rom[RegionOffset] >> 4;
    if (regionVal >= static_cast<int>(ERegion::SmsJapan) && regionVal <= static_cast<int>(ERegion::GgInternational))
    {
        region = static_cast<ERegion>(regionVal);
        LogInfo("Rom region = %s", RegionNames.at(region).c_str());
    }
    else
    {
        region = ERegion::Unknown;
        LogWarning("Unknown region value %d", regionVal);
    }

    isLoaded = true;
    return true;
}


void Cartridge::Reset()
{
    rom.clear();
    isLoaded = false;
}


}
