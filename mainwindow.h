#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include "ws_dictionary.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 主菜单 - 文件
    void on_action_open_triggered();
    void on_action_save_triggered();

    // 主界面 - 词典
    void on_lineedit_find_editingFinished();
    void on_tableview_dict_clicked(const QModelIndex &index);

    // 主界面 - 词条
    void on_pushbutton_edit_clicked();
    void on_pushbutton_save_clicked();
    void on_pushbutton_delete_clicked();
    void on_pushbutton_add_clicked();

private:
    Ui::MainWindow *ui;

    wintersun::DictionaryBase dict;
    QStandardItemModel *model_dict;

    int last_entry_num;
    bool is_change;

    void refreshTableviewDict();      // 显示词典
    void showInTextedit(const int &); // 显示词条
    void setChange(const bool &);     // 能否修改
    void saveChange();                // 保存修改
};
#endif // MAINWINDOW_H
