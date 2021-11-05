#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model_dict = new QStandardItemModel();

    ui->pushbutton_save->setVisible(false);
    ui->pushbutton_add->setVisible(false);

    ui->lineedit_find->setFixedHeight(ui->pushbutton_edit->sizeHint().height());
}

MainWindow::~MainWindow()
{
    delete ui;

    delete model_dict;
}

// ================================

void MainWindow::on_action_open_triggered() {
    try {
        dict.ReadFromFile("D://Repository/Qt/TestFile/SourceDev.md");

        last_entry_num = -1;
        is_change = false;
        refreshTableviewDict();
    } catch (const char *sz) {
        qDebug() << sz;
    }

    ui->pushbutton_add->setVisible(true);
}

void MainWindow::on_action_save_triggered() {
    try {
        dict.SaveToFile("D://Repository/Qt/TestFile/SourceDev.md");
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

// ================================

void MainWindow::on_lineedit_find_editingFinished() {
    if(ui->lineedit_find->text() == "") {
        refreshTableviewDict();
        return;
    }

    QVector<int> vec_tmp = dict.Search(ui->lineedit_find->text());
    model_dict->clear();

    for (int i = 0; i < vec_tmp.size(); i++) {
        model_dict->setItem(i, 0, new QStandardItem(dict.Display(vec_tmp[i]).Getter(0)));
    }

    ui->tableview_dict->setModel(model_dict);
}

void MainWindow::on_tableview_dict_clicked(const QModelIndex &index) {
    try {
        showInTextedit(index.row());
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

// ================================

void MainWindow::on_pushbutton_edit_clicked() { // 词条最少一个元素，编辑时两行（textedit编辑时自动添行）
    setChange(true);
}

void MainWindow::on_pushbutton_save_clicked() {
    try {
        saveChange();
    } catch (const char *sz) {
        qDebug() << sz;
    }

    setChange(false);
}

void MainWindow::on_pushbutton_delete_clicked() {
    try {
        dict.Delete(last_entry_num);

        refreshTableviewDict();
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

void MainWindow::on_pushbutton_add_clicked() {
    try {
        wintersun::EntryAbstract entry_tmp;
        dict.Add(entry_tmp);

        refreshTableviewDict();
    } catch (const char *sz) {
        qDebug() << sz;
    }
}

// ================================

void MainWindow::refreshTableviewDict() {
    model_dict->clear();

    for (int i = 0; i < dict.Size(); i++) {
        model_dict->setItem(i, 0, new QStandardItem(dict.Display(i).Getter(0)));
    }

    ui->tableview_dict->setModel(model_dict);
}

void MainWindow::showInTextedit(const int &row) {
    setChange(false);

    QString str_tmp("");
    last_entry_num = row;

    for (int m = 0, n = dict.Display(row).Size(); m < n; m++) {
        str_tmp = str_tmp + dict.Display(row).Getter(m) + "\n";
    }

    ui->textedit_entry->setText(str_tmp);
}

void MainWindow::setChange(const bool &b) {
    if (b) {
        is_change = true;
        ui->textedit_entry->setReadOnly(false);
        ui->pushbutton_save->setVisible(true);
        ui->pushbutton_edit->setVisible(false);
    }
    else {
        is_change = false;
        ui->textedit_entry->setReadOnly(true);
        ui->pushbutton_save->setVisible(false);
        ui->pushbutton_edit->setVisible(true);
    }
}

void MainWindow::saveChange() {
    wintersun::EntryAbstract entry_tmp;
    QStringList str_list = ui->textedit_entry->toPlainText().split("\n");

    for (int n = str_list.size() - 1; n >= 0; n--) {
        if (str_list[n] != "") {
            for (int i = 0; i <= n; i++) {
                entry_tmp.Setter(i, str_list[i]);
            }
            break;
        }
    }

    dict.Revise(last_entry_num, entry_tmp);
    refreshTableviewDict();
    showInTextedit(last_entry_num);
}
