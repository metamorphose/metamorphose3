#include <QtWidgets/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window(new RenamerModel(), new OperationFormModel());
    window.show();

    return app.exec();
}
