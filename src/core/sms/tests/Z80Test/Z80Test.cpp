#include <gtest/gtest.h>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

// Include the mocks first so they override subsequent includes.
#include "../CommonMocks/Memory.h"

#include "../../Z80.h"
#include "TestOpcodes.h"


namespace Sms
{


const QString JSON_PATH = "./test_data/z80/v1/";

class Z80Ex : public Z80
{
public:
    Z80Ex(Memory *memory) : Z80(memory) {}
    ~Z80Ex() = default;

    using Z80::reg;
    using Z80::iff1;
    using Z80::iff2;
};


class Z80Test : public ::testing::Test, public ::testing::WithParamInterface<TestOpcodeInfo>
{
protected:
    Z80Test()
    {
        memory = new Memory();
        cpu = new Z80Ex(memory);
    }

    ~Z80Test() override
    {
        delete cpu;
        delete memory;
    }

    void RunInstructionTest(const QString &opcodeName, const QString &opcode);
    void FormatData(const QJsonObject &obj, QString &str);

    Z80Ex *cpu;
    Memory *memory;
};


void Z80Test::RunInstructionTest(const QString &opcodeName, const QString &opcode)
{
    QString testName_ = opcodeName + ": ";

    QString filename = QStringLiteral("%1%2.json").arg(JSON_PATH).arg(opcode.toLower());
    QFile jsonFile(filename);
    ASSERT_TRUE(jsonFile.open(QIODevice::ReadOnly)) << qPrintable(testName_ + "Couldn't open " + filename);

    QJsonDocument json = QJsonDocument::fromJson(jsonFile.readAll());
    ASSERT_TRUE(json.isArray()) << qPrintable(testName_);
    QJsonArray array = json.array();

    for (int i = 0; i < array.size(); i++)
    {
        QJsonObject obj = array[i].toObject();

        testName_ = opcodeName + ": " + obj["name"].toString();
        const char *testName = testName_.toLocal8Bit().constData();

        // Set register initial values.
        QJsonObject initial = obj["initial"].toObject();
        cpu->reg.a = initial["a"].toInt();
        cpu->reg.b = initial["b"].toInt();
        cpu->reg.c = initial["c"].toInt();
        cpu->reg.d = initial["d"].toInt();
        cpu->reg.e = initial["e"].toInt();
        cpu->reg.f = initial["f"].toInt();
        cpu->reg.h = initial["h"].toInt();
        cpu->reg.l = initial["l"].toInt();
        cpu->reg.i = initial["i"].toInt();
        cpu->reg.r = initial["r"].toInt();
        cpu->reg.af_ = initial["af_"].toInt();
        cpu->reg.bc_ = initial["bc_"].toInt();
        cpu->reg.de_ = initial["de_"].toInt();
        cpu->reg.hl_ = initial["hl_"].toInt();
        cpu->reg.ix = initial["ix"].toInt();
        cpu->reg.iy = initial["iy"].toInt();
        cpu->reg.pc = initial["pc"].toInt();
        cpu->reg.sp = initial["sp"].toInt();
        cpu->reg.wz = initial["wz"].toInt();
        cpu->iff1 = initial["iff1"].toInt();
        cpu->iff2 = initial["iff2"].toInt();
        //cpu->reg.im = initial["im"].toInt();
        //cpu->reg.ei = initial["ei"].toInt();
        //cpu->reg.p = initial["p"].toInt();
        //cpu->reg.q = initial["q"].toInt();

        // Set RAM initial values.
        QJsonArray initialRam = initial["ram"].toArray();
        for (int j = 0; j < initialRam.size(); j++)
        {
            QJsonArray pair = initialRam[j].toArray();
            int32_t addr = pair[0].toInt();
            int32_t val = pair[1].toInt();
            ASSERT_GE(addr, 0) << testName;
            ASSERT_LE(addr, 0xFFFF) << testName;
            ASSERT_GE(val, 0) << testName;
            ASSERT_LE(val, 0xFF) << testName;
            memory->WriteByte(addr, val);
        }

        // Run the opcode.
        cpu->ProcessOpcode();

        // Verify result register values.
        QJsonObject final = obj["final"].toObject();
        EXPECT_EQ(cpu->reg.a, final["a"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.b, final["b"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.c, final["c"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.d, final["d"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.e, final["e"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.f, final["f"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.h, final["h"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.l, final["l"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.i, final["i"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.r, final["r"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.af_, final["af_"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.bc_, final["bc_"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.de_, final["de_"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.hl_, final["hl_"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.ix, final["ix"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.iy, final["iy"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.pc, final["pc"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.sp, final["sp"].toInt()) << testName;
        EXPECT_EQ(cpu->reg.wz, final["wz"].toInt()) << testName;
        EXPECT_EQ(cpu->iff1, final["iff1"].toInt()) << testName;
        EXPECT_EQ(cpu->iff2, final["iff2"].toInt()) << testName;
        //EXPECT_EQ(cpu->reg.im, final["im"].toInt()) << testName;
        //EXPECT_EQ(cpu->reg.ei, final["ei"].toInt()) << testName;
        //EXPECT_EQ(cpu->reg.p, final["p"].toInt()) << testName;
        //EXPECT_EQ(cpu->reg.q, final["q"].toInt()) << testName;

        // Verify result RAM values.
        QJsonArray finalRam = final["ram"].toArray();
        for (int j = 0; j < finalRam.size(); j++)
        {
            QJsonArray pair = finalRam[j].toArray();
            int32_t addr = pair[0].toInt();
            int32_t val = pair[1].toInt();
            ASSERT_GE(addr, 0) << testName;
            ASSERT_LE(addr, 0xFFFF) << testName;
            ASSERT_GE(val, 0) << testName;
            ASSERT_LE(val, 0xFF) << testName;
            EXPECT_EQ(memory->ReadByte(addr), val) << testName;
        }

        // If there were errors, stop processing this opcode. We don't want 10000 errors.
        if (HasNonfatalFailure())
        {
            QString str;
            FormatData(obj, str);
            qDebug("Encountered failure, not continuing.");
            qDebug("Test Data: %s", qPrintable(str));
            return;
        }
    }
}


void Z80Test::FormatData(const QJsonObject &obj, QString &str)
{
    str += "\nname: \"" + obj["name"].toString() + "\"\n";

    QJsonObject initial = obj["initial"].toObject();
    str += "initial: \n";
    str += QStringLiteral("\ta: 0x%1\n").arg(initial["a"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tb: 0x%1\n").arg(initial["b"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tc: 0x%1\n").arg(initial["c"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\td: 0x%1\n").arg(initial["d"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\te: 0x%1\n").arg(initial["e"].toInt(), 2, 16, QChar('0'));
    uint8_t f = initial["f"].toInt();
    str += QStringLiteral("\tf: 0x%1 (s=%2 z=%3 y=%4 h=%5 x=%6 p/v=%7 n=%8 c=%9)\n")
        .arg(f, 2, 16, QChar('0'))
        .arg(f >> 7)
        .arg((f >> 6) & 0x01)
        .arg((f >> 5) & 0x01)
        .arg((f >> 4) & 0x01)
        .arg((f >> 3) & 0x01)
        .arg((f >> 2) & 0x01)
        .arg((f >> 1) & 0x01)
        .arg(f & 0x01);
    str += QStringLiteral("\th: 0x%1\n").arg(initial["h"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tl: 0x%1\n").arg(initial["l"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\ti: 0x%1\n").arg(initial["i"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tr: 0x%1\n").arg(initial["r"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\taf_: 0x%1\n").arg(initial["af_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tbc_: 0x%1\n").arg(initial["bc_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tde_: 0x%1\n").arg(initial["de_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\thl_: 0x%1\n").arg(initial["hl_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tix: 0x%1\n").arg(initial["ix"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tiy: 0x%1\n").arg(initial["iy"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tpc: 0x%1\n").arg(initial["pc"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tsp: 0x%1\n").arg(initial["sp"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\twz: 0x%1\n").arg(initial["wz"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tiff1: 0x%1\n").arg(initial["iff1"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tiff2: 0x%1\n").arg(initial["iff2"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tim: 0x%1\n").arg(initial["im"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tei: 0x%1\n").arg(initial["ei"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tp: 0x%1\n").arg(initial["p"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tq: 0x%1\n").arg(initial["q"].toInt(), 2, 16, QChar('0'));

    QJsonArray initalRam = initial["ram"].toArray();
    str += "\tram: \n";
    QStringList initialRamStrings;
    for (int i = 0; i < initalRam.size(); i++)
    {
        QJsonArray pair = initalRam[i].toArray();
        initialRamStrings.append(QStringLiteral("\t\t0x%1 = 0x%2").arg(pair[0].toInt(), 6, 16, QChar('0')).arg(pair[1].toInt(), 2, 16, QChar('0')));
    }
    initialRamStrings.sort();
    str += initialRamStrings.join(QChar('\n')) + "\n";

    QJsonObject final = obj["final"].toObject();
    str += "expected: \n";
    str += QStringLiteral("\ta: 0x%1\n").arg(final["a"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tb: 0x%1\n").arg(final["b"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tc: 0x%1\n").arg(final["c"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\td: 0x%1\n").arg(final["d"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\te: 0x%1\n").arg(final["e"].toInt(), 2, 16, QChar('0'));
    f = final["f"].toInt();
    str += QStringLiteral("\tf: 0x%1 (s=%2 z=%3 y=%4 h=%5 x=%6 p/v=%7 n=%8 c=%9)\n")
        .arg(f, 2, 16, QChar('0'))
        .arg(f >> 7)
        .arg((f >> 6) & 0x01)
        .arg((f >> 5) & 0x01)
        .arg((f >> 4) & 0x01)
        .arg((f >> 3) & 0x01)
        .arg((f >> 2) & 0x01)
        .arg((f >> 1) & 0x01)
        .arg(f & 0x01);
    str += QStringLiteral("\th: 0x%1\n").arg(final["h"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tl: 0x%1\n").arg(final["l"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\ti: 0x%1\n").arg(final["i"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tr: 0x%1\n").arg(final["r"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\taf_: 0x%1\n").arg(final["af_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tbc_: 0x%1\n").arg(final["bc_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tde_: 0x%1\n").arg(final["de_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\thl_: 0x%1\n").arg(final["hl_"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tix: 0x%1\n").arg(final["ix"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tiy: 0x%1\n").arg(final["iy"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tpc: 0x%1\n").arg(final["pc"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tsp: 0x%1\n").arg(final["sp"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\twz: 0x%1\n").arg(final["wz"].toInt(), 4, 16, QChar('0'));
    str += QStringLiteral("\tiff1: 0x%1\n").arg(final["iff1"].toInt(), 2, 16, QChar('0'));
    str += QStringLiteral("\tiff2: 0x%1\n").arg(final["iff2"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tim: 0x%1\n").arg(final["im"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tei: 0x%1\n").arg(final["ei"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tp: 0x%1\n").arg(final["p"].toInt(), 2, 16, QChar('0'));
    //str += QStringLiteral("\tq: 0x%1\n").arg(final["q"].toInt(), 2, 16, QChar('0'));

    QJsonArray finalRam = final["ram"].toArray();
    str += "\tram: \n";
    QStringList finalRamStrings;
    for (int i = 0; i < finalRam.size(); i++)
    {
        QJsonArray pair = finalRam[i].toArray();
        finalRamStrings.append(QStringLiteral("\t\t0x%1 = 0x%2").arg(pair[0].toInt(), 6, 16, QChar('0')).arg(pair[1].toInt(), 2, 16, QChar('0')));
    }
    finalRamStrings.sort();
    str += finalRamStrings.join(QChar('\n')) + "\n";

    str += "actual: \n";
    str += QStringLiteral("\ta: 0x%1\n").arg(cpu->reg.a, 2, 16, QChar('0'));
    str += QStringLiteral("\tb: 0x%1\n").arg(cpu->reg.b, 2, 16, QChar('0'));
    str += QStringLiteral("\tc: 0x%1\n").arg(cpu->reg.c, 2, 16, QChar('0'));
    str += QStringLiteral("\td: 0x%1\n").arg(cpu->reg.d, 2, 16, QChar('0'));
    str += QStringLiteral("\te: 0x%1\n").arg(cpu->reg.e, 2, 16, QChar('0'));
    f = cpu->reg.f;
    str += QStringLiteral("\tp: 0x%1 (s=%2 z=%3 y=%4 h=%5 x=%6 p/v=%7 n=%8 c=%9)\n")
        .arg(f, 2, 16, QChar('0'))
        .arg(f >> 7)
        .arg((f >> 6) & 0x01)
        .arg((f >> 5) & 0x01)
        .arg((f >> 4) & 0x01)
        .arg((f >> 3) & 0x01)
        .arg((f >> 2) & 0x01)
        .arg((f >> 1) & 0x01)
        .arg(f & 0x01);
    str += QStringLiteral("\th: 0x%1\n").arg(cpu->reg.h, 2, 16, QChar('0'));
    str += QStringLiteral("\tl: 0x%1\n").arg(cpu->reg.l, 2, 16, QChar('0'));
    str += QStringLiteral("\ti: 0x%1\n").arg(cpu->reg.i, 2, 16, QChar('0'));
    str += QStringLiteral("\tr: 0x%1\n").arg(cpu->reg.r, 2, 16, QChar('0'));
    str += QStringLiteral("\taf_: 0x%1\n").arg(cpu->reg.af_, 4, 16, QChar('0'));
    str += QStringLiteral("\tbc_: 0x%1\n").arg(cpu->reg.bc_, 4, 16, QChar('0'));
    str += QStringLiteral("\tde_: 0x%1\n").arg(cpu->reg.de_, 4, 16, QChar('0'));
    str += QStringLiteral("\thl_: 0x%1\n").arg(cpu->reg.hl_, 4, 16, QChar('0'));
    str += QStringLiteral("\tix: 0x%1\n").arg(cpu->reg.ix, 4, 16, QChar('0'));
    str += QStringLiteral("\tiy: 0x%1\n").arg(cpu->reg.iy, 4, 16, QChar('0'));
    str += QStringLiteral("\tpc: 0x%1\n").arg(cpu->reg.pc, 4, 16, QChar('0'));
    str += QStringLiteral("\tsp: 0x%1\n").arg(cpu->reg.sp, 4, 16, QChar('0'));
    str += QStringLiteral("\twz: 0x%1\n").arg(cpu->reg.wz, 4, 16, QChar('0'));
    str += QStringLiteral("\tiff1: 0x%1\n").arg(cpu->iff1, 2, 16, QChar('0'));
    str += QStringLiteral("\tiff2: 0x%1\n").arg(cpu->iff2, 2, 16, QChar('0'));
    //str += QStringLiteral("\tim: 0x%1\n").arg(cpu->reg.im, 2, 16, QChar('0'));
    //str += QStringLiteral("\tei: 0x%1\n").arg(cpu->reg.ei, 2, 16, QChar('0'));
    //str += QStringLiteral("\tp: 0x%1\n").arg(cpu->reg.p, 2, 16, QChar('0'));
    //str += QStringLiteral("\tq: 0x%1\n").arg(cpu->reg.q, 2, 16, QChar('0'));

    str += "\tram: \n";
    QStringList expectedRamStrings;
    for (int i = 0; i < finalRam.size(); i++)
    {
        QJsonArray pair = finalRam[i].toArray();
        expectedRamStrings.append(QStringLiteral("\t\t0x%1 = 0x%2").arg(pair[0].toInt(), 6, 16, QChar('0')).arg(memory->ReadByte(pair[0].toInt()), 2, 16, QChar('0')));
    }
    expectedRamStrings.sort();
    str += expectedRamStrings.join(QChar('\n')) + "\n";
}


// Get implemented opcodes. Delete this when all are implemented.
std::vector<TestOpcodeInfo> GetTestingOpcodes()
{
    std::vector<TestOpcodeInfo> info;
    info.reserve(2048);

    uint8_t implemented[] = {
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4F,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5F,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6F,
                                                  0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7F,
        0xF9,
        0x06, 0x0E, 0x16, 0x1E, 0x26, 0x2E, 0x3E,
        0x46, 0x4E, 0x56, 0x5E, 0x66, 0x6E, 0x7E, 0x0A, 0x1A,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x77, 0x02, 0x12,  0x32,
        0x36, 0x3A, 0x01, 0x11, 0x21, 0x31, 0x2A, 0x22,
        0xC5, 0xD5, 0xE5, 0xF5, 0xC1, 0xD1, 0xE1, 0xF1,
        0xEB, 0x08, 0xD9, 0xE3,
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0xC6, 0x09, 0x19, 0x29, 0x39,
        0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0xCE,
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0xD6,
        0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xDE,
        0x04, 0x0C, 0x14, 0x1C, 0x24, 0x2C, 0x34, 0x3C, 0x03, 0x13, 0x23, 0x33,
        0x05, 0x0D, 0x15, 0x1D, 0x25, 0x2D, 0x35, 0x3D, 0x0B, 0x1B, 0x2B, 0x3B,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xE6,
        0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xF6,
        0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xFE,
        0x07, 0x0F, 0x17, 0x1F,
    };
    for (uint8_t i : implemented)
    {
        info.push_back(TestOpcodeTable[i]);
        info.push_back(TestOpcodeTableDD[i]);
        info.push_back(TestOpcodeTableFD[i]);
    }

    uint8_t implementedED[] = {
        0x47, 0x4F, 0x57, 0x5F, 0x4B, 0x5B, 0x6B, 0x7B, 0x43, 0x53, 0x63, 0x73,
        0xA0, 0xB0, 0xA8, 0xB8, 0xA1, 0xB1, 0xA9, 0xB9,
        0x4A, 0x5A, 0x6A, 0x7A, 0x42, 0x52, 0x62, 0x72,
    };
    for (uint8_t i : implementedED)
        info.push_back(TestOpcodeTableED[i]);

    info.insert(info.end(), TestOpcodeTableCB.begin(), TestOpcodeTableCB.end());
    info.insert(info.end(), TestOpcodeTableDDCB.begin(), TestOpcodeTableDDCB.end());
    info.insert(info.end(), TestOpcodeTableFDCB.begin(), TestOpcodeTableFDCB.end());


    return info;
}


INSTANTIATE_TEST_SUITE_P(
    Opcodes,
    Z80Test,
    ::testing::ValuesIn(GetTestingOpcodes()),
    [](const ::testing::TestParamInfo<TestOpcodeInfo> &info) {
        return (QString(info.param.opcode).replace(' ', '_') + "_" + info.param.name).toStdString();
    }
);


TEST_P(Z80Test, Opcode) {
    const TestOpcodeInfo &op = GetParam();
    RunInstructionTest(op.name, op.opcode);
}


}