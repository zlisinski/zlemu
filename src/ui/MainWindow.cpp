#include <core/sms/Emulator.h>

#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Logger::SetOutput(this);
    Logger::SetLogLevel(LogLevel::eTrace);
    Logger::SetTraceLevel(0xFFFFFFFF);

    emulator = new Sms::Emulator();
    emulator->LoadRom("US-European BIOS v1.3 (1986).sms");
}


MainWindow::~MainWindow()
{
    delete emulator;
}


void MainWindow::Output(std::unique_ptr<LogEntry> entry)
{
    printf("%s\n", entry->message.c_str());
}
