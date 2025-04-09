#include <QApplication>
#include "mainwindow.h"
#include "antidebug.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Проверка отладчика
    AntiDebug::checkDebugger();


    MainWindow w;
    w.show();
    return a.exec();
}
