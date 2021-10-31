#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_open_triggered()
{
    dict.ReadFromFile("D://Repository/Visual Studio/WordRem/WordRem/x64/Debug/Test.txt");

    QStandardItemModel* model = new QStandardItemModel();

    model->setItem(0, 0, new QStandardItem("Hello world!")); // 后期优化转换

    ui->dict_view->setModel(model);
}
