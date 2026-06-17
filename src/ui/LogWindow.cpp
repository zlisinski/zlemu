#include <iomanip>
#include <sstream>

#include "LogWindow.h"
#include "Settings.h"
#include "ui_LogWindow.h"

extern Settings settings;


LogWindow::LogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);

    restoreGeometry(settings.logWindowGeometry);

    SetTraceCheckboxEnabled(false);

    switch (Logger::GetLogLevel())
    {
        case LogLevel::eError:
            ui->rbError->setChecked(true);
            break;
        case LogLevel::eWarning:
            ui->rbWarning->setChecked(true);
            break;
        case LogLevel::eInfo:
            ui->rbInfo->setChecked(true);
            break;
        case LogLevel::eDebug:
            ui->rbDebug->setChecked(true);
            break;
        case LogLevel::eTrace:
            ui->rbTrace->setChecked(true);
            SetTraceCheckboxEnabled(true);
            break;
    }

    uint32_t traceLevel = Logger::GetTraceLevel();
    ui->chkCpu->setChecked(traceLevel & static_cast<uint32_t>(TraceLogLevel::eCpu));
    ui->chkDisplay->setChecked(traceLevel & static_cast<uint32_t>(TraceLogLevel::eDisplay));
    ui->chkMemory->setChecked(traceLevel & static_cast<uint32_t>(TraceLogLevel::eMemory));
    ui->chkInput->setChecked(traceLevel & static_cast<uint32_t>(TraceLogLevel::eInput));
    ui->chkTimer->setChecked(traceLevel & static_cast<uint32_t>(TraceLogLevel::eTimer));
    ui->chkInterrupt->setChecked(traceLevel & static_cast<uint32_t>(TraceLogLevel::eInterrupt));
    ui->chkAudio->setChecked(traceLevel & static_cast<uint32_t>(TraceLogLevel::eAudio));

    connect(this, &LogWindow::SignalMessageReady, this, &LogWindow::SlotOutputMessage, Qt::QueuedConnection);
}


LogWindow::~LogWindow()
{
    delete ui;
}


void LogWindow::closeEvent(QCloseEvent *event)
{
    settings.logWindowGeometry = saveGeometry();
    settings.Save();

    emit SignalLogWindowClosed();

    QWidget::closeEvent(event);
}


void LogWindow::Output(std::unique_ptr<LogEntry> entry)
{
    // This function runs in the thread context of the Emulator worker thread, or whoever called Log().
    QMutexLocker lock(&entriesMutex);

    entries.push_back(std::move(entry));

    lock.unlock();

    // Signal the main thread to add the text.
    emit SignalMessageReady();
}


void LogWindow::SlotOutputMessage()
{
    QMutexLocker lock(&entriesMutex);

    for (const auto &entry : entries)
    {
        char timeBuf[9];
        tm *now = localtime(&entry->tv.tv_sec);
        strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", now);
        if (entry->level == LogLevel::eTrace)
        {
            // These come in too fast for the GUI, so just print them.
            printf("%s.%06ld: %s\n", timeBuf, entry->tv.tv_usec, entry->message.c_str());
        }
        else
        {
            printf("%s.%06ld: %s\n", timeBuf, entry->tv.tv_usec, entry->message.c_str());
            ui->txtOutput->append(QStringLiteral("%1.%2: %3")
                .arg(timeBuf)
                .arg(entry->tv.tv_usec, 6, QChar('0'))
                .arg(entry->message.c_str()));
        }
    }

    entries.clear();
}


void LogWindow::SetTraceCheckboxEnabled(bool enable)
{
    ui->chkCpu->setEnabled(enable);
    ui->chkDisplay->setEnabled(enable);
    ui->chkMemory->setEnabled(enable);
    ui->chkInput->setEnabled(enable);
    ui->chkTimer->setEnabled(enable);
    ui->chkInterrupt->setEnabled(enable);
    ui->chkAudio->setEnabled(enable);
}


void LogWindow::SetTraceLevel(TraceLogLevel subsystem, bool checked)
{
    uint32_t newLevel = Logger::GetTraceLevel();
    if (checked)
        newLevel |= static_cast<uint32_t>(subsystem);
    else
        newLevel &= ~static_cast<uint32_t>(subsystem);

    settings.traceLevel = newLevel;
    settings.Save();
    Logger::SetTraceLevel(newLevel);
}


void LogWindow::on_rbError_clicked()
{
    settings.logLevel = static_cast<int>(LogLevel::eError);
    settings.Save();
    Logger::SetLogLevel(LogLevel::eError);
    SetTraceCheckboxEnabled(false);
}


void LogWindow::on_rbWarning_clicked()
{
    settings.logLevel = static_cast<int>(LogLevel::eWarning);
    settings.Save();
    Logger::SetLogLevel(LogLevel::eWarning);
    SetTraceCheckboxEnabled(false);
}


void LogWindow::on_rbInfo_clicked()
{
    settings.logLevel = static_cast<int>(LogLevel::eInfo);
    settings.Save();
    Logger::SetLogLevel(LogLevel::eInfo);
    SetTraceCheckboxEnabled(false);
}


void LogWindow::on_rbDebug_clicked()
{
    settings.logLevel = static_cast<int>(LogLevel::eDebug);
    settings.Save();
    Logger::SetLogLevel(LogLevel::eDebug);
    SetTraceCheckboxEnabled(false);
}


void LogWindow::on_rbTrace_clicked()
{
    settings.logLevel = static_cast<int>(LogLevel::eTrace);
    settings.Save();
    Logger::SetLogLevel(LogLevel::eTrace);
    SetTraceCheckboxEnabled(true);
}


void LogWindow::on_chkCpu_clicked(bool checked)
{
    SetTraceLevel(TraceLogLevel::eCpu, checked);
}


void LogWindow::on_chkDisplay_clicked(bool checked)
{
    SetTraceLevel(TraceLogLevel::eDisplay, checked);
}


void LogWindow::on_chkMemory_clicked(bool checked)
{
    SetTraceLevel(TraceLogLevel::eMemory, checked);
}


void LogWindow::on_chkInput_clicked(bool checked)
{
    SetTraceLevel(TraceLogLevel::eInput, checked);
}


void LogWindow::on_chkTimer_clicked(bool checked)
{
    SetTraceLevel(TraceLogLevel::eTimer, checked);
}


void LogWindow::on_chkInterrupt_clicked(bool checked)
{
    SetTraceLevel(TraceLogLevel::eInterrupt, checked);
}


void LogWindow::on_chkAudio_clicked(bool checked)
{
    SetTraceLevel(TraceLogLevel::eAudio, checked);
}
