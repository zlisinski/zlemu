#include <gtest/gtest.h>

#include "../TestLogger.h"
#include "../../Memory.h"



namespace Sms
{

constexpr int BankSize = 0x4000;

class MemoryEx : public Memory
{
public:
    MemoryEx() {}
    ~MemoryEx() = default;

    using Memory::memory;
    using Memory::wram;
    using Memory::sram;
    using Memory::bios;
    using Memory::rom;
    using Memory::memoryControlRegister;
    using Memory::isCartEnabled;
    using Memory::isBiosEnabled;
    using Memory::isSramEnabled;
    using Memory::currentSramBank;
};


class MemoryTest : public ::testing::Test
{
protected:
    MemoryTest()
    {
        constexpr int BankCount = 8;
        std::vector<uint8_t> rom(BankSize * BankCount);
        for (int i = 0; i < BankCount; ++i)
        {
            std::fill_n(&rom[(i * BankSize)], BankSize, static_cast<uint8_t>(i+1));
        }

        memory = new MemoryEx();
        memory->SetRom(rom);
        memory->Reset();

        std::fill_n(&memory->sram[0], BankSize, 0x80);
        std::fill_n(&memory->sram[BankSize], BankSize, 0x81);
    }

    ~MemoryTest() override
    {
        delete memory;
    }

    MemoryEx *memory;
    TestLogger logger;
};


TEST_F(MemoryTest, MapSram_MapRomBank0)
{
    memory->WriteByte(0xFFFD, 0x07);
    EXPECT_EQ(memory->memory[0], 0x01);
    EXPECT_EQ(memory->memory[0x3FF], 0x01);
    EXPECT_EQ(memory->memory[0x400], 0x08);
    EXPECT_EQ(memory->memory[0x3FFF], 0x08);
}


TEST_F(MemoryTest, MapSram_MapRomBank1)
{
    memory->WriteByte(0xFFFE, 0x07);
    EXPECT_EQ(memory->memory[0x4000], 0x08);
    EXPECT_EQ(memory->memory[0x7FFF], 0x08);
}


TEST_F(MemoryTest, MapSram_MapRomBank2)
{
    memory->WriteByte(0xFFFF, 0x07);
    EXPECT_EQ(memory->memory[0x8000], 0x08);
    EXPECT_EQ(memory->memory[0xBFFF], 0x08);
}


TEST_F(MemoryTest, MapSram_MapRomBank2WhenSRAMIsActive)
{
    memory->isSramEnabled = true;
    memory->WriteByte(0xFFFF, 0x07);
    EXPECT_EQ(memory->memory[0x8000], 0x03);
    EXPECT_EQ(memory->memory[0xBFFF], 0x03);
}


TEST_F(MemoryTest, MapSram_EnablingBank1)
{
    memory->isSramEnabled = false;
    memory->WriteByte(0xFFFC, 0x08);

    EXPECT_EQ(memory->memory[0x8000], 0x80);
    EXPECT_EQ(memory->memory[0xBFFF], 0x80);
}


TEST_F(MemoryTest, MapSram_EnablingBank2)
{
    memory->isSramEnabled = false;
    memory->WriteByte(0xFFFC, 0x0C);

    EXPECT_EQ(memory->memory[0x8000], 0x81);
    EXPECT_EQ(memory->memory[0xBFFF], 0x81);
}


TEST_F(MemoryTest, MapSram_DisableSram)
{
    std::fill_n(&memory->memory[0x8000], BankSize, 0xA0);
    memory->wram[0x1FFF] = 3;
    memory->currentSramBank = 1;
    memory->isSramEnabled = true;
    memory->WriteByte(0xFFFC, 0x00);

    EXPECT_EQ(memory->memory[0x8000], 0x04);
    EXPECT_EQ(memory->memory[0xBFFF], 0x04);
    EXPECT_EQ(memory->sram[0x4000], 0xA0);
    EXPECT_EQ(memory->sram[0x7FFF], 0xA0);
}


TEST_F(MemoryTest, MapSram_AlreadyEnabledSwitchToBank0)
{
    std::fill_n(&memory->memory[0x8000], BankSize, 0xA0);
    memory->currentSramBank = 1;
    memory->isSramEnabled = true;
    memory->WriteByte(0xFFFC, 0x08);

    EXPECT_EQ(memory->memory[0x8000], 0x80);
    EXPECT_EQ(memory->memory[0xBFFF], 0x80);
    EXPECT_EQ(memory->sram[0x4000], 0xA0);
    EXPECT_EQ(memory->sram[0x7FFF], 0xA0);
}


TEST_F(MemoryTest, MapSram_AlreadyEnabledSwitchToBank1)
{
    std::fill_n(&memory->memory[0x8000], BankSize, 0xA0);
    memory->currentSramBank = 0;
    memory->isSramEnabled = true;
    memory->WriteByte(0xFFFC, 0x0C);

    EXPECT_EQ(memory->memory[0x8000], 0x81);
    EXPECT_EQ(memory->memory[0xBFFF], 0x81);
    EXPECT_EQ(memory->sram[0], 0xA0);
    EXPECT_EQ(memory->sram[0x3FFF], 0xA0);
}


}