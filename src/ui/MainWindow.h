#ifndef ZLEMU_UI_MAINWINDOW_H
#define ZLEMU_UI_MAINWINDOW_H

#include <QApplication>
#include <QElapsedTimer>
#include <QMainWindow>
#include <QtGamepad>

#include "../core/Buttons.h"
#include "../core/Logger.h"
#include "../core/DisplayInterface.h"


class AbsEmulator;
class LogWindow;
class QGraphicsView;
class QLabel;


class MainWindow : public QMainWindow, public DisplayInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void FrameReady(const std::array<uint32_t, 256 * 240> &displayFrameBuffer) override;
    void RequestMessageBox(const std::string &message) override;

protected:
    void OpenRom(QString filename, bool saveToRecent = true);
    void UpdateRecentFile(const QString &filename);
    void UpdateRecentFilesActions();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void SetupMenuBar();
    void SetupStatusBar();
    void SetupKeyBindings();
    void SetupGamepad();
    void SetDisplayScale(int scale);

    AbsEmulator *emulator = nullptr;

    std::array<uint32_t, 256 * 240> frameBuffer = {};

    QGraphicsView *graphicsView = nullptr;
    QLabel *labelFps = nullptr;
    QLabel *labelPause = nullptr;

    QElapsedTimer frameCapTimer;
    QElapsedTimer fpsTimer;
    int frameCount = 0;

    QList<QAction *> recentFilesActions;
    QMenu *recentFileMenu = nullptr;

    LogWindow *logWindow = nullptr;
    QAction *displayLogWindowAction = nullptr;

    QHash<Qt::Key, Buttons::Button> keyboardBindings;
    QHash<QGamepadManager::GamepadButton, Buttons::Button> gamepadBindings;
    QGamepad *gamepad = nullptr;

signals:
    void SignalFrameReady();

protected slots:
    void onFrameReady();
    void onLogWindowClosed();
};


#endif