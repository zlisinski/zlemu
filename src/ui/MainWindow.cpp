#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QStatusBar>
#include <core/sms/Emulator.h>

#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Logger::SetOutput(this);
    Logger::SetLogLevel(LogLevel::eTrace);
    Logger::SetTraceLevel(0xFFFFFFFF);

    connect(this, &MainWindow::SignalFrameReady, this, &MainWindow::onFrameReady, Qt::QueuedConnection);

    SetupStatusBar();

    graphicsView = new QGraphicsView(this);
    graphicsView->setFrameStyle(QFrame::NoFrame);
    setCentralWidget(graphicsView);
    QGraphicsScene *scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    SetDisplayScale(2);

    fpsTimer.start();

    emulator = new Sms::Emulator(this);
    emulator->LoadRom("US-European BIOS v1.3 (1986).sms");
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
    pixmap->setScale(2);
}


void MainWindow::FrameReady(const std::array<uint32_t, 256 * 240> &displayFrameBuffer)
{
    // This function runs in the thread context of the Emulator worker thread.

    // Copy data so Emulator thread doesn't change data while we're drawing the screen.
    frameBuffer = displayFrameBuffer;

    // Signal the main thread to draw the screen.
    emit SignalFrameReady();
}


void MainWindow::RequestMessageBox(const std::string &message)
{
    (void)message;
}


void MainWindow::Output(std::unique_ptr<LogEntry> entry)
{
    char timeBuf[9];
    tm *now = localtime(&entry->tv.tv_sec);
    strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", now);
    printf("%s.%06ld: %s\n", timeBuf, entry->tv.tv_usec, entry->message.c_str());
}


void MainWindow::SetupStatusBar()
{
    labelFps = new QLabel("0 FPS", this);
    labelPause = new QLabel("", this);
    statusBar()->addPermanentWidget(labelFps);
    statusBar()->addPermanentWidget(labelPause);
}


void MainWindow::SetDisplayScale(int scale)
{
    graphicsView->scene()->clear();
    graphicsView->setSceneRect(0, 0, 256*scale, 240*scale);
    graphicsView->setFixedSize(256*scale, 240*scale);
    adjustSize();
    displayScale = scale;
}
