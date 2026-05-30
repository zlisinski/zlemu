#include <QElapsedTimer>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

// Include the mocks first so they override subsequent includes.
#include "../CommonMocks/Memory.h"

#include "../../Z80.h"
#include "../Z80Test/TestOpcodes.h"


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


class Z80Test
{
public:
    Z80Test()
    {
        memory = new Memory();
        cpu = new Z80Ex(memory);
    }

    ~Z80Test()
    {
        delete cpu;
        delete memory;
    }

    void RunInstructionTest(const QString &opcodeName, const QString &opcode);

    Z80Ex *cpu;
    Memory *memory;
};


void Z80Test::RunInstructionTest(const QString &opcodeName, const QString &opcode)
{
    QString testName_ = opcodeName + ": ";

    QString filename = QStringLiteral("%1%2.json").arg(JSON_PATH).arg(opcode.toLower());
    QFile jsonFile(filename);
    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        printf("%s\n", qPrintable(testName_ + "Couldn't open " + filename));
        return;
    }

    QJsonDocument json = QJsonDocument::fromJson(jsonFile.readAll());
    QJsonArray array = json.array();

    QElapsedTimer timer;
    quint64 elapsed = 0;

    for (int i = 0; i < array.size(); i++)
    {
        QJsonObject obj = array[i].toObject();

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
        //cpu->reg.wz = initial["wz"].toInt();
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
            memory->WriteByte(addr, val);
        }

        // Run the opcode.
        timer.start();
        cpu->ProcessOpcode();
        elapsed += timer.nsecsElapsed();
    }

    QString str = QStringLiteral("'%1', '%2'").arg(opcodeName, 30, ' ').arg(elapsed);
    printf("%s\n", qPrintable(str));
}


// Get implemented opcodes. Delete this when all are implemented.
std::vector<TestOpcodeInfo> GetTestingOpcodes()
{
    std::vector<TestOpcodeInfo> info;

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

    uint8_t implementedCB[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
        0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
        0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    };
    for (uint8_t i : implementedCB)
    {
        info.push_back(TestOpcodeTableCB[i]);
        info.push_back(TestOpcodeTableDDCB[i]);
        info.push_back(TestOpcodeTableFDCB[i]);
    }

    return info;
}


}


int main()
{
    std::vector<TestOpcodeInfo> opcodes = Sms::GetTestingOpcodes();

    for (TestOpcodeInfo info : opcodes)
    {
        Sms::Z80Test *test = new Sms::Z80Test();
        QString name = QString(info.opcode) + " " + info.name;

        test->RunInstructionTest(name, info.opcode);

        delete test;
    }
}