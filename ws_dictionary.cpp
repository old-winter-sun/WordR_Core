#include "ws_dictionary.h"

#include <QFile>
#include <QTextStream>
#include <QPointer>

namespace wintersun {

const QString DictionaryAbstract::kSplitEntry = QChar(0x1D);

DictionaryAbstract::DictionaryAbstract() { }

DictionaryAbstract::~DictionaryAbstract() { }

// 操作：================================

void DictionaryAbstract::Add(const EntryAbstract &entry) {
	entries_.push_back(entry);
}

void DictionaryAbstract::Delete(const int index) {
    if (index < 0 || entries_.size() <= index)
        throw "WS_DICTIONARY: Invaild Entry Index";
    entries_.erase(entries_.constBegin() + index);
}

void DictionaryAbstract::Revise(const int index, const EntryAbstract &entry) {
    if (index < 0 || entries_.size() <= index)
        throw "WS_DICTIONARY: Invaild Entry Index";
	entries_[index] = entry;
}

// 按拼写查找
QVector<int> DictionaryAbstract::Search(const QString &str) {
    QVector<int> vec_index;
	for (int i = 0; i < entries_.size(); i++) {
        if (entries_[i].Getter(0) == str)
            vec_index.push_back(i);
	}
    return vec_index;
}

// 信息：================================

int DictionaryAbstract::Size() {
    return entries_.size();
}

EntryAbstract DictionaryAbstract::Display(const int index) {
    if (index < 0 || entries_.size() <= index)
        throw "WS_DICTIONARY: Invaild Entry Index";
    return entries_[index];
}

// 文件流：================================

void DictionaryAbstract::SaveToFile(const QString &str_path) {
    QFile file(str_path);

    QString str_tmp;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw "WS_DICTIONARY: Open File Failed";

    for (int n = 0; n < entries_.size(); n++) {
        for (int i = 0; i < entries_[n].Size(); i++) {
            str_tmp = entries_[n].Getter(i) + "\n";
            file.write(str_tmp.toUtf8());
        }
        file.write((kSplitEntry + "\n").toUtf8());
    }

    file.close();

    return;
}

void DictionaryAbstract::ReadFromFile(const QString &str_path) {
    QFile file(str_path);

    QString str_get;
    QScopedPointer<EntryAbstract> entry_tmp(new EntryAbstract);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw "WS_DICTIONARY: Open File Failed";

    QTextStream stream_get(&file);

    for (int i = 0; !stream_get.atEnd(); i++) {
        str_get = stream_get.readLine();

        if (str_get == kSplitEntry) {
            i = -1;
            entries_.push_back(*entry_tmp);
            entry_tmp.reset(new EntryAbstract);
        }
        else
            entry_tmp->Setter(i, str_get);
    }

	file.close();

    return;
}

} // namespace wintersun
