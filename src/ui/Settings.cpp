#include <QSettings>

#include "Settings.h"


void Settings::Load()
{
    QSettings settings;

    mainWindowGeometry = settings.value("MainWindow/Geometry").toByteArray();
    logWindowGeometry = settings.value("LogWindow/Geometry").toByteArray();
    logWindowEnabled = settings.value("LogWindow/Enabled").toBool();

    frameCap = settings.value("Display/FrameCap", 60).toInt();
    displayScale = settings.value("Display/Scale", 1).toInt();

    logLevel = settings.value("Logging/LogLevel", 0).toInt();
    traceLevel = settings.value("Logging/TraceLevel", 0).toInt();

    lastRomDirectory = settings.value("Files/LastRomDir").toString();
    recentFilesList = settings.value("Files/RecentFilesList").toStringList();

    settings.beginGroup("Sms");
    sms.biosEnabled = settings.value("Bios/Enabled", false).toBool();
    sms.biosFilename = settings.value("Bios/Filename").toString();
    sms.keyUp = settings.value("Input/KeyUp").value<Qt::Key>();
    sms.keyDown = settings.value("Input/KeyDown").value<Qt::Key>();
    sms.keyLeft = settings.value("Input/KeyLeft").value<Qt::Key>();
    sms.keyRight = settings.value("Input/KeyRight").value<Qt::Key>();
    sms.keyButton1 = settings.value("Input/KeyButton1").value<Qt::Key>();
    sms.keyButton2 = settings.value("Input/KeyButton2").value<Qt::Key>();
    sms.keyPause = settings.value("Input/KeyPause").value<Qt::Key>();
    sms.padUp = settings.value("Input/PadUp").value<QGamepadManager::GamepadButton>();
    sms.padDown = settings.value("Input/PadDown").value<QGamepadManager::GamepadButton>();
    sms.padLeft = settings.value("Input/PadLeft").value<QGamepadManager::GamepadButton>();
    sms.padRight = settings.value("Input/PadRight").value<QGamepadManager::GamepadButton>();
    sms.padButton1 = settings.value("Input/PadButton1").value<QGamepadManager::GamepadButton>();
    sms.padButton2 = settings.value("Input/PadButton2").value<QGamepadManager::GamepadButton>();
    sms.padPause = settings.value("Input/PadPause").value<QGamepadManager::GamepadButton>();
    settings.endGroup();
}


void Settings::Save() const
{
    QSettings settings;

    settings.setValue("MainWindow/Geometry", mainWindowGeometry);
    settings.setValue("LogWindow/Geometry", logWindowGeometry);
    settings.setValue("LogWindow/Enabled", logWindowEnabled);

    settings.setValue("Display/FrameCap", frameCap);
    settings.setValue("Display/Scale", displayScale);

    settings.setValue("Logging/LogLevel", logLevel);
    settings.setValue("Logging/TraceLevel", traceLevel);

    settings.setValue("Files/LastRomDir", lastRomDirectory);
    settings.setValue("Files/RecentFilesList", recentFilesList);

    settings.beginGroup("Sms");
    settings.setValue("Bios/Enabled", sms.biosEnabled);
    settings.setValue("Bios/Filename", sms.biosFilename);
    settings.setValue("Input/KeyUp", sms.keyUp);
    settings.setValue("Input/KeyDown", sms.keyDown);
    settings.setValue("Input/KeyLeft", sms.keyLeft);
    settings.setValue("Input/KeyRight", sms.keyRight);
    settings.setValue("Input/KeyButton1", sms.keyButton1);
    settings.setValue("Input/KeyButton2", sms.keyButton2);
    settings.setValue("Input/KeyPause", sms.keyPause);
    settings.setValue("Input/PadUp", sms.padUp);
    settings.setValue("Input/PadDown", sms.padDown);
    settings.setValue("Input/PadLeft", sms.padLeft);
    settings.setValue("Input/PadRight", sms.padRight);
    settings.setValue("Input/PadButton1", sms.padButton1);
    settings.setValue("Input/PadButton2", sms.padButton2);
    settings.setValue("Input/PadPause", sms.padPause);
    settings.endGroup();
}
