#include <QElapsedTimer>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

// Include the mocks first so they override subsequent includes.
#include "../CommonMocks/Memory.h"
#include "../CommonMocks/Timer.h"

#include "../TestLogger.h"
#include "../../Interrupt.h"
#include "../../Z80.h"
#include "../Z80Test/TestOpcodes.h"


namespace Sms
{


const QString JSON_PATH = "./test_data/z80/v1/";

class Z80Ex : public Z80
{
public:
    Z80Ex(Memory *memory, Timer *timer, Interrupt *interrupt) : Z80(memory, timer, interrupt) {}
    ~Z80Ex() = default;

    using Z80::reg;
    using Z80::halted;
    using Z80::iff1;
    using Z80::iff2;
    using Z80::im;
    using Z80::ei;
};


class Z80Test
{
public:
    Z80Test()
    {
        memory = new Memory();
        interrupt = new Interrupt();
        timer = new Timer(nullptr, nullptr);
        cpu = new Z80Ex(memory, timer, interrupt);
    }

    ~Z80Test()
    {
        delete cpu;
        delete memory;
    }

    void RunInstructionTest(const QString &opcodeName, const QString &opcode);

    Z80Ex *cpu;
    Memory *memory;
    Timer *timer;
    Interrupt *interrupt;
    TestLogger logger;
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
        cpu->reg.wz = initial["wz"].toInt();
        cpu->iff1 = initial["iff1"].toInt();
        cpu->iff2 = initial["iff2"].toInt();
        cpu->im = initial["im"].toInt();
        cpu->ei = initial["ei"].toInt();
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

        // Set port initial values.
        QJsonArray ports = obj["ports"].toArray();
        for (int j = 0; j < ports.size(); j++)
        {
            QJsonArray port = ports[j].toArray();

            // Test data assumes NMOS value, but I'm emulating CMOS.
            if (opcode == "ED 71" && port[1].toInt() == 0)
            {
                port[1] = 255;
                ports[j] = port;
            }

            if (port[2].toString() == "r")
            {
                uint8_t p = port[0].toInt() & 0xFF;
                uint8_t v = port[1].toInt() & 0xFF;
                memory->WritePort(p, v);
            }
        }

        // Run the opcode.
        timer.start();
        cpu->ProcessOpcode();
        elapsed += timer.nsecsElapsed();
    }

    QString str = QStringLiteral("\"%1\", \"%2\"").arg(opcodeName, 30, ' ').arg(elapsed);
    printf("%s\n", qPrintable(str));
}


// Get implemented opcodes. Only add tests that have test files.
std::vector<TestOpcodeInfo> GetTestingOpcodes()
{
    std::vector<TestOpcodeInfo> info;
    info.reserve(2048);

    QDir dir(JSON_PATH);
    QStringList nameFilter;

    nameFilter.append("??.json");
    QFileInfoList fileList = dir.entryInfoList(nameFilter, QDir::Files, QDir::Name);
    for (const QFileInfo &fileInfo : fileList)
    {
        int op = fileInfo.fileName().mid(0, 2).toInt(nullptr, 16);
        info.push_back(TestOpcodeTable[op]);
        info.push_back(TestOpcodeTableDD[op]);
        info.push_back(TestOpcodeTableFD[op]);
    }

    nameFilter.clear();
    nameFilter.append("ed ??.json");
    fileList = dir.entryInfoList(nameFilter, QDir::Files, QDir::Name);
    for (const QFileInfo &fileInfo : fileList)
    {
        int op = fileInfo.fileName().mid(3, 2).toInt(nullptr, 16);
        info.push_back(TestOpcodeTableED[op]);
    }

    // These tables are fully populated.
    info.insert(info.end(), TestOpcodeTableCB.begin(), TestOpcodeTableCB.end());
    info.insert(info.end(), TestOpcodeTableDDCB.begin(), TestOpcodeTableDDCB.end());
    info.insert(info.end(), TestOpcodeTableFDCB.begin(), TestOpcodeTableFDCB.end());

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