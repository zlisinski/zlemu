#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <core/sms/Emulator.h>

#include "LogWindow.h"
#include "MainWindow.h"
#include "Settings.h"
#include "UiUtils.h"


constexpr int MAX_RECENT_FILES = 20;

Settings settings;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QCoreApplication::setOrganizationName("zlisinski");
    QCoreApplication::setApplicationName("zlemu");
    settings.Load();

    Logger::SetLogLevel(static_cast<LogLevel>(settings.logLevel));
    Logger::SetTraceLevel(settings.traceLevel);
    logWindow = new LogWindow(this);
    connect(logWindow, &LogWindow::SignalLogWindowClosed, this, &MainWindow::onLogWindowClosed);
    if (settings.logWindowEnabled)
        logWindow->show();
    Logger::SetOutput(logWindow);

    restoreGeometry(settings.mainWindowGeometry);

    SetupMenuBar();
    SetupStatusBar();
    SetupKeyBindings();
    SetupGamepad();

    graphicsView = new QGraphicsView(this);
    graphicsView->setFrameStyle(QFrame::NoFrame);
    setCentralWidget(graphicsView);
    QGraphicsScene *scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    SetDisplayScale(settings.displayScale);

    fpsTimer.start();
    frameCapTimer.start();

    emulator = new Sms::Emulator(this);

    connect(this, &MainWindow::SignalFrameReady, this, &MainWindow::onFrameReady, Qt::QueuedConnection);
}


MainWindow::~MainWindow()
{
    delete emulator;
}


void MainWindow::onFrameReady()
{
    uint64_t elapsedTime = fpsTimer.elapsed();

    if (elapsedTime > 1000)
    {
        int fps = frameCount / (elapsedTime / 1000.0);
        labelFps->setText(QString::number(fps) + " FPS");
        fpsTimer.restart();
        frameCount = 0;
    }
    else
    {
        frameCount++;
    }

    QImage img((uchar *)(&frameBuffer[0]), 256, 240, QImage::Format_RGB32);
    graphicsView->scene()->clear();
    QGraphicsPixmapItem *pixmap = graphicsView->scene()->addPixmap(QPixmap::fromImage(img));
    pixmap->setScale(settings.displayScale);
}


void MainWindow::FrameReady(const std::array<uint32_t, 256 * 240> &displayFrameBuffer)
{
    // This function runs in the thread context of the Emulator worker thread.

    // Copy data so Emulator thread doesn't change data while we're drawing the screen.
    frameBuffer = displayFrameBuffer;

    // Signal the main thread to draw the screen.
    emit SignalFrameReady();

    int64_t elapsedTime = frameCapTimer.elapsed();

    if (settings.frameCap > 0)
    {
        const double frameMillis = 1.0 / settings.frameCap * 1000;
        if (elapsedTime < frameMillis)
        {
            // Block the Emulator from running to limit frame rate.
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(frameMillis - elapsedTime)));
        }
    }

    frameCapTimer.restart();
}


void MainWindow::RequestMessageBox(const std::string &message)
{
    (void)message;
}


// Don't make filename a reference, since this can be called from the recent file menu, which we will destroy in here.
// I'll fix this better later.
void MainWindow::OpenRom(QString filename, bool saveToRecent)
{
    if (filename != "")
    {
        if (saveToRecent)
            UpdateRecentFile(filename);

        if (settings.sms.biosEnabled)
        {
            QFile file(settings.sms.biosFilename);
            if (!file.open(QIODevice::ReadOnly))
            {
                UiUtils::MessageBox("Error opening bios file " + settings.sms.biosFilename);
                return;
            }
            QByteArray byteArray = file.readAll();
            file.close();
            emulator->SetBios(std::vector<uint8_t>(byteArray.begin(), byteArray.end()));
        }

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            UiUtils::MessageBox("Error opening rom file " + filename);
            return;
        }
        QByteArray byteArray = file.readAll();
        file.close();
        emulator->SetRom(std::vector<uint8_t>(byteArray.begin(), byteArray.end()));

        if (!emulator->StartEmulation())
        {
            UiUtils::MessageBox("Error starting emulation");
            return;
        }

        setWindowTitle("ZLEMU - " + filename);
    }
}


void MainWindow::UpdateRecentFile(const QString &filename)
{
    settings.recentFilesList.removeAll(filename);
    settings.recentFilesList.prepend(filename);
    while (settings.recentFilesList.size() > MAX_RECENT_FILES)
        settings.recentFilesList.removeLast();
    settings.Save();
    UpdateRecentFilesActions();
}


void MainWindow::UpdateRecentFilesActions()
{
    recentFilesActions.clear();
    recentFileMenu->clear();
    for (const QString &filename : settings.recentFilesList)
        recentFileMenu->addAction(filename, [&]{OpenRom(filename);});
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    Buttons::Button button = keyboardBindings.value(static_cast<Qt::Key>(event->key()), Buttons::Button::eButtonNone);
    if (button != Buttons::Button::eButtonNone)
        emulator->ButtonPressed(button);
    else
        QMainWindow::keyPressEvent(event);
}


void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    Buttons::Button button = keyboardBindings.value(static_cast<Qt::Key>(event->key()), Buttons::Button::eButtonNone);
    if (button != Buttons::Button::eButtonNone)
        emulator->ButtonReleased(button);
    else
        QMainWindow::keyReleaseEvent(event);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (emulator)
        emulator->EndEmulation();

    settings.mainWindowGeometry = saveGeometry();
    settings.Save();

    QMainWindow::closeEvent(event);
}


void MainWindow::SetupMenuBar()
{
    menuBar()->setNativeMenuBar(false);

    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&Open ROM...", [this]
    {
        QString filename = QFileDialog::getOpenFileName(this, "Open ROM File", settings.lastRomDirectory);
        if (!filename.isEmpty())
        {
            QFileInfo info(filename);
            settings.lastRomDirectory = info.absolutePath();
            settings.Save();
        }
        OpenRom(filename);
    });

    recentFileMenu = fileMenu->addMenu("Open &Recent");
    UpdateRecentFilesActions();

    fileMenu->addSeparator();
    fileMenu->addAction("&Settings...", []{});
    fileMenu->addSeparator();
    fileMenu->addAction("&Quit", [this]{this->close();});

    QMenu *emuMenu = menuBar()->addMenu("&Emulator");
    emuMenu->addAction("&Reset", [this]{if (emulator) {emulator->Reset();}});
    QAction *pauseAction = emuMenu->addAction("&Pause", [this](bool checked)
    {
        if (emulator)
        {
            labelPause->setText(checked ? "Paused" : "");
            emulator->Pause(checked);
        }
    }, Qt::Key_Escape);
    pauseAction->setCheckable(true);
    emuMenu->addAction("&End Emulation", [this]{if (emulator) {emulator->EndEmulation();}});

    QMenu *emuSpeedMenu = emuMenu->addMenu("&Speed");
    QActionGroup *emuSpeedGroup = new QActionGroup(this);
    std::pair<QString, int> speedVals[4] = {{"&Half", 30}, {"&Normal", 60}, {"&Double", 120}, {"&Uncapped", 0}};
    for (const auto &speedVal : speedVals)
    {
        QAction *action = emuSpeedGroup->addAction(speedVal.first);
        action->setCheckable(true);
        if (speedVal.second == settings.frameCap)
            action->setChecked(true);
        connect(action, &QAction::triggered, [=]
        {
            settings.frameCap = speedVal.second;
            settings.Save();
        });
        emuSpeedMenu->addAction(action);
    }

    QMenu *displayMenu = menuBar()->addMenu("&Display");
    QMenu *displaySizeMenu = displayMenu->addMenu("&Size");
    QActionGroup *displaySizeGroup = new QActionGroup(this);
    for (int i = 1; i < 6; i++)
    {
        QAction *action = displaySizeGroup->addAction(QString("&%1x").arg(i));
        action->setCheckable(true);
        if (i == settings.displayScale)
            action->setChecked(true);
        connect(action, &QAction::triggered, [this, i]
        {
            SetDisplayScale(i);
        });
        displaySizeMenu->addAction(action);
    }

    displayMenu->addSeparator();
    displayLogWindowAction = displayMenu->addAction("&Log Window", [this](bool checked)
    {
        settings.logWindowEnabled = checked;
        settings.Save();
        if (checked)
            logWindow->show();
        else
            logWindow->hide();
    });
    displayLogWindowAction->setCheckable(true);
    displayLogWindowAction->setChecked(settings.logWindowEnabled);
}


void MainWindow::SetupStatusBar()
{
    labelFps = new QLabel("0 FPS", this);
    labelPause = new QLabel("", this);
    statusBar()->addPermanentWidget(labelFps);
    statusBar()->addPermanentWidget(labelPause);
}


void MainWindow::SetupKeyBindings()
{
    keyboardBindings = {
        {settings.sms.keyUp, Buttons::eButtonUp},
        {settings.sms.keyDown, Buttons::eButtonDown},
        {settings.sms.keyLeft, Buttons::eButtonLeft},
        {settings.sms.keyRight, Buttons::eButtonRight},
        {settings.sms.keyButton1, Buttons::eButton1},
        {settings.sms.keyButton2, Buttons::eButton2},
        {settings.sms.keyPause, Buttons::eButtonPause}
    };

    gamepadBindings = {
        {settings.sms.padUp, Buttons::eButtonUp},
        {settings.sms.padDown, Buttons::eButtonDown},
        {settings.sms.padLeft, Buttons::eButtonLeft},
        {settings.sms.padRight, Buttons::eButtonRight},
        {settings.sms.padButton1, Buttons::eButton1},
        {settings.sms.padButton2, Buttons::eButton2},
        {settings.sms.padPause, Buttons::eButtonPause}
    };
}


void MainWindow::SetupGamepad()
{
    QList<int> gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty())
        return;

    gamepad = new QGamepad(*gamepads.begin(), this);

    connect(QGamepadManager::instance(), &QGamepadManager::gamepadButtonPressEvent, this,
        [this](int deviceId, QGamepadManager::GamepadButton gamepadButton, double value)
        {
            Q_UNUSED(deviceId);
            Q_UNUSED(value);
            Buttons::Button button = gamepadBindings.value(gamepadButton, Buttons::Button::eButtonNone);
            if (button != Buttons::Button::eButtonNone)
                emulator->ButtonPressed(button);
        });
    connect(QGamepadManager::instance(), &QGamepadManager::gamepadButtonReleaseEvent, this,
        [this](int deviceId, QGamepadManager::GamepadButton gamepadButton)
        {
            Q_UNUSED(deviceId);
            Buttons::Button button = gamepadBindings.value(gamepadButton, Buttons::Button::eButtonNone);
            if (button != Buttons::Button::eButtonNone)
                emulator->ButtonReleased(button);
        });
}


void MainWindow::SetDisplayScale(int scale)
{
    graphicsView->scene()->clear();
    graphicsView->setSceneRect(0, 0, 256*scale, 240*scale);
    graphicsView->setFixedSize(256*scale, 240*scale);
    adjustSize();
    settings.displayScale = scale;
    settings.Save();
}


void MainWindow::onLogWindowClosed()
{
    displayLogWindowAction->setChecked(false);
}