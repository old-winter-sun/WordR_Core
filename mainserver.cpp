#include "mainwindow.h"

#ifndef BE_QTWINAPPLICATION

constexpr qint64 kMaxSocketRead = 1024;

// 后端
// 构造析构函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 后端 - 初始化
    p_server_ = new QTcpServer;

    if(p_server_->listen(QHostAddress::LocalHost, 1234))
        qDebug() << "服务器正常开启！";
    else
        qDebug() << "服务器开启失败！请检查IP及端口";

    // 后端 - 连接槽函数
    connect(p_server_, &QTcpServer::newConnection, this, &MainWindow::newConnect);
}

MainWindow::~MainWindow()
{
    delete model_dict_;
}

// ================================
void MainWindow::newConnect() {
    p_socket_ = p_server_->nextPendingConnection();

    qDebug() << "已连接！";
    qDebug() << "客户端地址：" << p_socket_->localAddress();
    qDebug() << "所连接端口：" << p_socket_->localPort();

    p_socket_->write("Hello WordR");
    p_socket_->flush();

    connect(p_socket_, &QTcpSocket::readyRead, this, &MainWindow::readData);
}

void MainWindow::readData() { // 后续优化
    QByteArray client_bytes = p_socket_->readLine(kMaxSocketRead);
    QString client_str;
    client_str.prepend(client_bytes);

    if(client_str == "open")
//        else if

}

#endif
