#include "mainwindow.h"

#include <QApplication>
#include <QByteArray>

int main(int argc, char *argv[])
{
    // Force the native macOS platform plugin for the GUI app.
    // This avoids inheriting an offscreen/headless Qt platform from the environment.
#ifdef Q_OS_MACOS
    qputenv("QT_QPA_PLATFORM", QByteArray("cocoa"));
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.raise();
    w.activateWindow();
    return a.exec();
}
