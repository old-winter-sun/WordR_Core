#include "mainwindow.h"

#include <QApplication>

#ifdef BE_QTWINAPPLICATION
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#else
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    return a.exec();
}
#endif
