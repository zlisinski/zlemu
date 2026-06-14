#ifndef ZLEMU_UI_MAINWINDOW_H
#define ZLEMU_UI_MAINWINDOW_H

#include <QApplication>
#include <QElapsedTimer>
#include <QMainWindow>

#include "../core/Logger.h"
#include "../core/DisplayInterface.h"


class AbsEmulator;
class QGraphicsView;
class QLabel;


class MainWindow : public QMainWindow, public LoggerOutput, public DisplayInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void FrameReady(const std::array<uint32_t, 256 * 240> &displayFrameBuffer) override;
    void RequestMessageBox(const std::string &message) override;

    void Output(std::unique_ptr<LogEntry> entry) override;

protected:
    void SetupStatusBar();
    void SetDisplayScale(int scale);

    AbsEmulator *emulator = nullptr;

    std::array<uint32_t, 256 * 240> frameBuffer = {};
    int displayScale = 1;

    QGraphicsView *graphicsView = nullptr;
    QLabel *labelFps = nullptr;
    QLabel *labelPause = nullptr;

    // Frame cap variables.
    QElapsedTimer frameCapTimer;
    int frameCapSetting = 0;

    // FPS variables.
    QElapsedTimer fpsTimer;
    int frameCount = 0;

signals:
    void SignalFrameReady();

protected slots:
    void onFrameReady();
};


#endif