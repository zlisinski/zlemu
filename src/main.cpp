#include <QApplication>
#include "ui/MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("zlisinski");
    app.setApplicationName("zlemu");

    MainWindow window;
    window.show();

    return app.exec();
}