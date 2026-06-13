#ifndef ZLEMU_UI_MAINWINDOW_H
#define ZLEMU_UI_MAINWINDOW_H

#include <QMainWindow>

#include "../core/Logger.h"


class AbsEmulator;


class MainWindow : public QMainWindow, public LoggerOutput
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void Output(std::unique_ptr<LogEntry> entry) override;

protected:
    AbsEmulator *emulator = nullptr;
};


#endif