#include "SupervisorMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<uint8_t>();

    QApplication a(argc, argv);
    SupervisorMainWindow w;
    w.show();

    return a.exec();
}
