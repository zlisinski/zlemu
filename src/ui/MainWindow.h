#ifndef ZLEMU_UI_MAINWINDOW_H
#define ZLEMU_UI_MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};


#endif