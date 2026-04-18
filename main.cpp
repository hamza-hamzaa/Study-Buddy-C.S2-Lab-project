#include "clientcontroller.h"
#include "qtnetworkclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtNetworkClient* network = new QtNetworkClient();
    ClientController controller(network);
    controller.start();
    return QCoreApplication::exec();
}

