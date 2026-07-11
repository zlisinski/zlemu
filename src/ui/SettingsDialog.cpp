#include <QHash>
#include <QtWidgets>

#include "KeyBindingDialog.h"
#include "Settings.h"
#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

extern Settings settings;


// Only support Xbox button namees for now.
static const QHash<QGamepadManager::GamepadButton, QString> GamepadButtonNames = {
    {QGamepadManager::ButtonInvalid, "Unbound"},
    {QGamepadManager::ButtonA, "A"},
    {QGamepadManager::ButtonB, "B"},
    {QGamepadManager::ButtonX, "X"},
    {QGamepadManager::ButtonY, "Y"},
    {QGamepadManager::ButtonL1, "L1"},
    {QGamepadManager::ButtonR1, "R1"},
    {QGamepadManager::ButtonL2, "L2"},
    {QGamepadManager::ButtonR2, "R2"},
    {QGamepadManager::ButtonSelect, "Select"},
    {QGamepadManager::ButtonStart, "Start"},
    {QGamepadManager::ButtonL3, "L3"},
    {QGamepadManager::ButtonR3, "R3"},
    {QGamepadManager::ButtonUp, "Up"},
    {QGamepadManager::ButtonDown, "Down"},
    {QGamepadManager::ButtonRight, "Right"},
    {QGamepadManager::ButtonLeft, "Left"},
    {QGamepadManager::ButtonCenter, "Center"},
    {QGamepadManager::ButtonGuide, "Guide"}
};


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    keyBindings = {
        {Buttons::eButtonUp, settings.sms.keyUp},
        {Buttons::eButtonDown, settings.sms.keyDown},
        {Buttons::eButtonLeft, settings.sms.keyLeft},
        {Buttons::eButtonRight, settings.sms.keyRight},
        {Buttons::eButton1, settings.sms.keyButton1},
        {Buttons::eButton2, settings.sms.keyButton2},
        {Buttons::eButtonPause, settings.sms.keyPause}
    };

    padBindings = {
        {Buttons::eButtonUp, settings.sms.padUp},
        {Buttons::eButtonDown, settings.sms.padDown},
        {Buttons::eButtonLeft, settings.sms.padLeft},
        {Buttons::eButtonRight, settings.sms.padRight},
        {Buttons::eButton1, settings.sms.padButton1},
        {Buttons::eButton2, settings.sms.padButton2},
        {Buttons::eButtonPause, settings.sms.padPause}
    };

    UpdateKeyBindingButtonText();

    // Add custom property to each button, so we can use one slot for all {key,pad} buttons.
    ui->btnUpKey->setProperty("buttonId", Buttons::eButtonUp);
    ui->btnDownKey->setProperty("buttonId", Buttons::eButtonDown);
    ui->btnLeftKey->setProperty("buttonId", Buttons::eButtonLeft);
    ui->btnRightKey->setProperty("buttonId", Buttons::eButtonRight);
    ui->btn1Key->setProperty("buttonId", Buttons::eButton1);
    ui->btn2Key->setProperty("buttonId", Buttons::eButton2);
    ui->btnPauseKey->setProperty("buttonId", Buttons::eButtonPause);

    ui->btnUpPad->setProperty("buttonId", Buttons::eButtonUp);
    ui->btnDownPad->setProperty("buttonId", Buttons::eButtonDown);
    ui->btnLeftPad->setProperty("buttonId", Buttons::eButtonLeft);
    ui->btnRightPad->setProperty("buttonId", Buttons::eButtonRight);
    ui->btn1Pad->setProperty("buttonId", Buttons::eButton1);
    ui->btn2Pad->setProperty("buttonId", Buttons::eButton2);
    ui->btnPausePad->setProperty("buttonId", Buttons::eButtonPause);

    keyButtons = {ui->btnUpKey, ui->btnDownKey, ui->btnLeftKey, ui->btnRightKey,
                  ui->btn1Key, ui->btn2Key, ui->btnPauseKey};
    padButtons = {ui->btnUpPad, ui->btnDownPad, ui->btnLeftPad, ui->btnRightPad,
                  ui->btn1Pad, ui->btn2Pad, ui->btnPausePad};

    for (QPushButton *button : keyButtons)
        connect(button, &QPushButton::clicked, this, &SettingsDialog::onInputBindKey);
    for (QPushButton *button : padButtons)
        connect(button, &QPushButton::clicked, this, &SettingsDialog::onInputBindPad);
}


SettingsDialog::~SettingsDialog()
{
    delete ui;
}


void SettingsDialog::accept()
{
    SaveSettings();

    QDialog::accept();
}


void SettingsDialog::closeEvent(QCloseEvent *event)
{
    if (dirty)
    {
        QMessageBox msg(QMessageBox::Warning, "Unsaved changes",
                        "There are unsaved changes. Do you want to save them?",
                        QMessageBox::Save | QMessageBox::Discard, this);

        if (msg.exec() == QMessageBox::Save)
            SaveSettings();
    }

    QWidget::closeEvent(event);
}


void SettingsDialog::SaveSettings()
{
    settings.sms.keyUp = keyBindings[Buttons::eButtonUp];
    settings.sms.keyDown = keyBindings[Buttons::eButtonDown];
    settings.sms.keyLeft = keyBindings[Buttons::eButtonLeft];
    settings.sms.keyRight = keyBindings[Buttons::eButtonRight];
    settings.sms.keyButton1 = keyBindings[Buttons::eButton1];
    settings.sms.keyButton2 = keyBindings[Buttons::eButton2];
    settings.sms.keyPause = keyBindings[Buttons::eButtonPause];

    settings.sms.padUp = padBindings[Buttons::eButtonUp];
    settings.sms.padDown = padBindings[Buttons::eButtonDown];
    settings.sms.padLeft = padBindings[Buttons::eButtonLeft];
    settings.sms.padRight = padBindings[Buttons::eButtonRight];
    settings.sms.padButton1 = padBindings[Buttons::eButton1];
    settings.sms.padButton2 = padBindings[Buttons::eButton2];
    settings.sms.padPause = padBindings[Buttons::eButtonPause];

    settings.Save();
}


QString SettingsDialog::GetKeyString(Qt::Key keycode) const
{
    switch (keycode)
    {
        case Qt::Key_unknown:
            return "Unbound";
        case Qt::Key_Shift:
            return "Shift";
        case Qt::Key_Control:
            return "Control";
        case Qt::Key_Alt:
            return "Alt";
        case Qt::Key_Meta:
            return "Meta";
        default:
            return QKeySequence(keycode).toString();
    }
}


void SettingsDialog::UpdateKeyBindingButtonText()
{
    ui->btnUpKey->setText(GetKeyString(keyBindings[Buttons::eButtonUp]));
    ui->btnDownKey->setText(GetKeyString(keyBindings[Buttons::eButtonDown]));
    ui->btnLeftKey->setText(GetKeyString(keyBindings[Buttons::eButtonLeft]));
    ui->btnRightKey->setText(GetKeyString(keyBindings[Buttons::eButtonRight]));
    ui->btn1Key->setText(GetKeyString(keyBindings[Buttons::eButton1]));
    ui->btn2Key->setText(GetKeyString(keyBindings[Buttons::eButton2]));
    ui->btnPauseKey->setText(GetKeyString(keyBindings[Buttons::eButtonPause]));

    ui->btnUpPad->setText(GamepadButtonNames[padBindings[Buttons::eButtonUp]]);
    ui->btnDownPad->setText(GamepadButtonNames[padBindings[Buttons::eButtonDown]]);
    ui->btnLeftPad->setText(GamepadButtonNames[padBindings[Buttons::eButtonLeft]]);
    ui->btnRightPad->setText(GamepadButtonNames[padBindings[Buttons::eButtonRight]]);
    ui->btn1Pad->setText(GamepadButtonNames[padBindings[Buttons::eButton1]]);
    ui->btn2Pad->setText(GamepadButtonNames[padBindings[Buttons::eButton2]]);
    ui->btnPausePad->setText(GamepadButtonNames[padBindings[Buttons::eButtonPause]]);
}


void SettingsDialog::onInputBindKey()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button == nullptr)
        return;

    Buttons::Button buttonId = static_cast<Buttons::Button>(button->property("buttonId").toInt());
    KeyBindingDialog dialog(true, buttonId, this);
    dialog.setModal(true);
    if (dialog.exec())
    {
        Qt::Key key = static_cast<Qt::Key>(dialog.key);
        keyBindings[buttonId] = key;

        // TODO: Handle duplicate keys.

        UpdateKeyBindingButtonText();

        dirty = true;
    }
}


void SettingsDialog::onInputBindPad()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button == nullptr)
        return;

    Buttons::Button buttonId = static_cast<Buttons::Button>(button->property("buttonId").toInt());
    KeyBindingDialog dialog(false, buttonId, this);
    dialog.setModal(true);
    if (dialog.exec())
    {
        QGamepadManager::GamepadButton key = static_cast<QGamepadManager::GamepadButton>(dialog.key);
        padBindings[buttonId] = key;

        // TODO: Handle duplicate keys.

        UpdateKeyBindingButtonText();

        dirty = true;
    }
}