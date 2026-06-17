#ifndef ZLEMU_UI_SETTINGS_H
#define ZLEMU_UI_SETTINGS_H

#include <QByteArray>
#include <QGamepadManager>
#include <QString>


struct Settings
{
    Settings() {Load();}
    void Load();
    void Save() const;

    QByteArray mainWindowGeometry;
    QByteArray logWindowGeometry;
    bool logWindowEnabled;

    int frameCap;
    int displayScale;

    int logLevel;
    uint32_t traceLevel;

    QString lastRomDirectory;
    QStringList recentFilesList;

    struct SmsSettings
    {
        bool biosEnabled;
        QString biosFilename;

        Qt::Key keyUp;
        Qt::Key keyDown;
        Qt::Key keyLeft;
        Qt::Key keyRight;
        Qt::Key keyButton1;
        Qt::Key keyButton2;
        Qt::Key keyPause;

        QGamepadManager::GamepadButton padUp;
        QGamepadManager::GamepadButton padDown;
        QGamepadManager::GamepadButton padLeft;
        QGamepadManager::GamepadButton padRight;
        QGamepadManager::GamepadButton padButton1;
        QGamepadManager::GamepadButton padButton2;
        QGamepadManager::GamepadButton padPause;
    } sms;
};


#endif
