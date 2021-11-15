#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <QTextStream>

#include <cstdio>

// Qt界面
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

// 若运行CLI命令行界面，在QtCreator中左侧项目->Build & Run->Run(运行设置)->运行->Run in terminal勾选
int main()
{
    qDebug() << "Hello World";

    system("pause");

    return 0;
}
