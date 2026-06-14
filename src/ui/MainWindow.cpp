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
    char timeBuf[9];
    tm *now = localtime(&entry->tv.tv_sec);
    strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", now);
    printf("%s.%06ld: %s\n", timeBuf, entry->tv.tv_usec, entry->message.c_str());
}
