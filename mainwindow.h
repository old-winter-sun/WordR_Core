#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QTcpServer>
#include <QTcpSocket>

#include "maincompileswitch.h"
#include "ws_dictionary.h"

#define BE_QTWINAPPLICATION // 添加编译为Qt桌面应用

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// 基础
private:
    wintersun::DictionaryBase dict_;
    QString str_path;

    QStandardItemModel* model_dict_;

#ifdef BE_QTWINAPPLICATION
// Qt桌面应用
private:
    Ui::MainWindow *ui;

    int last_entry_num_;
    bool is_change_;

    // Qt桌面应用 - 辅助函数
    void RefreshTableviewDict();      // 显示词典
    void ShowInTextedit(const int &); // 显示词条
    void SetChange(const bool &);     // 能否修改
    void SaveChange();                // 保存修改

private slots:
    // Qt桌面应用 - 文件
    void on_action_open_triggered();
    void on_action_save_triggered();

    // Qt桌面应用 - 词典
    void on_lineedit_find_editingFinished();
    void on_tableview_dict_clicked(const QModelIndex &index);

    // Qt桌面应用 - 词条
    void on_pushbutton_edit_clicked();
    void on_pushbutton_save_clicked();
    void on_pushbutton_delete_clicked();
    void on_pushbutton_add_clicked();

#else
// WordR后端
private:
    QTcpServer* p_server_;
    QTcpSocket* p_socket_;

private slots:
    void newConnect();
    void readData();

#endif
};

#endif // MAINWINDOW_H
