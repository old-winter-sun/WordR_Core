#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

#ifdef BE_QTWINAPPLICATION

// Qt桌面应用
// 构造析构函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化
    model_dict_ = new QStandardItemModel();

    ui->pushbutton_save->setVisible(false);
    ui->pushbutton_add->setVisible(false);

    ui->lineedit_find->setFixedHeight(ui->pushbutton_edit->sizeHint().height());

    // 连接信号和槽函数
}

MainWindow::~MainWindow()
{
    delete ui;

    delete model_dict_;
}

// 辅助函数：================================
void MainWindow::RefreshTableviewDict() {
    model_dict_->clear();

    for (int i = 0; i < dict_.Size(); i++) {
        model_dict_->setItem(i, 0, new QStandardItem(dict_.Display(i).Get(0)));
    }

    ui->tableview_dict->setModel(model_dict_);
}

void MainWindow::ShowInTextedit(const int &row) {
    SetChange(false);

    QString str_tmp("");
    last_entry_num_ = row;

    for (int m = 0, n = dict_.Display(row).Size(); m < n; m++) {
        str_tmp = str_tmp + dict_.Display(row).Get(m) + "\n";
    }

    ui->textedit_entry->setText(str_tmp);
}

void MainWindow::SetChange(const bool &b) {
    if (b) {
        is_change_ = true;
        ui->textedit_entry->setReadOnly(false);
        ui->pushbutton_save->setVisible(true);
        ui->pushbutton_edit->setVisible(false);
    }
    else {
        is_change_ = false;
        ui->textedit_entry->setReadOnly(true);
        ui->pushbutton_save->setVisible(false);
        ui->pushbutton_edit->setVisible(true);
    }
}

void MainWindow::SaveChange() {
    QSharedPointer<wintersun::EntryAbstract> p_entry_tmp(new wintersun::EntryFree);
    QStringList str_list = ui->textedit_entry->toPlainText().split("\n");

    for (int n = str_list.size() - 1; n >= 0; n--) {
        if (str_list[n] != "") {
            p_entry_tmp->Set(0, str_list[0]);
            for (int i = 1; i <= n; i++) {
                p_entry_tmp->Add(str_list[i]);
            }
            break;
        }
    }

    dict_.Revise(last_entry_num_, p_entry_tmp);
    RefreshTableviewDict();
    ShowInTextedit(last_entry_num_);
}

// 文件：================================
void MainWindow::on_action_open_triggered() {
    try {
        str_path = QFileDialog::getOpenFileName(this, "open", "D:/_Repository/_OLD/Qt/TestFile/");
        dict_.ReadFromFile(str_path);

        last_entry_num_ = -1;
        is_change_ = false;
        RefreshTableviewDict();
    } catch (const char *sz) {
        qDebug() << sz;
    }

    ui->pushbutton_add->setVisible(true);
}

void MainWindow::on_action_save_triggered() {
    try {
        dict_.SaveToFile(str_path);
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

// 词典：================================
void MainWindow::on_lineedit_find_editingFinished() {
    if(ui->lineedit_find->text() == "") {
        RefreshTableviewDict();
        return;
    }

    QVector<int> vec_tmp = dict_.Search(ui->lineedit_find->text());
    model_dict_->clear();

    for (int i = 0; i < vec_tmp.size(); i++) {
        model_dict_->setItem(i, 0, new QStandardItem(dict_.Display(vec_tmp[i]).Get(0)));
    }

    ui->tableview_dict->setModel(model_dict_);
}

void MainWindow::on_tableview_dict_clicked(const QModelIndex &index) {
    try {
        ShowInTextedit(index.row());
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

// 词条：================================
void MainWindow::on_pushbutton_edit_clicked() { // 词条最少一个元素，编辑时两行（textedit编辑时自动添行）
    SetChange(true);
}

void MainWindow::on_pushbutton_save_clicked() {
    try {
        SaveChange();
    } catch (const char *sz) {
        qDebug() << sz;
    }

    SetChange(false);
}

void MainWindow::on_pushbutton_delete_clicked() {
    try {
        dict_.Delete(last_entry_num_);

        RefreshTableviewDict();
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

void MainWindow::on_pushbutton_add_clicked() {
    try {
        QSharedPointer<wintersun::EntryAbstract> p_entry_tmp(new wintersun::EntryFree);
        dict_.Add(p_entry_tmp);

        RefreshTableviewDict();
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

#endif
