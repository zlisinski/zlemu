#pragma once

#include <QGamepadManager>
#include <QDialog>

#include "../core/Buttons.h"


namespace Ui {
class SettingsDialog;
}


class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog() override;

    void accept() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void SaveSettings();
    QString GetKeyString(Qt::Key keycode) const;
    void UpdateKeyBindingButtonText();

    Ui::SettingsDialog *ui;

    QVector<QPushButton*> keyButtons;
    QVector<QPushButton*> padButtons;
    QHash<Buttons::Button, Qt::Key> keyBindings;
    QHash<Buttons::Button, QGamepadManager::GamepadButton> padBindings;

    bool dirty = false;

private slots:
    void onInputBindKey();
    void onInputBindPad();
};