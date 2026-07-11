#pragma once

#include <QDialog>
#include <QtGamepad/QGamepadManager>

#include "../core/Buttons.h"


namespace Ui {
class KeyBindingDialog;
}


class QGamepadManager;


class KeyBindingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBindingDialog(bool isKeyboard, Buttons::Button buttonId, QWidget *parent = 0);
    ~KeyBindingDialog() override;

    int key;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::KeyBindingDialog *ui;

    bool isKeyboard;

private slots:
    void onGamepadPressed(int deviceId, QGamepadManager::GamepadButton button, double value);
};
