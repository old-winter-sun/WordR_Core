#include "ws_dictionary.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

namespace wintersun {

const QString DictionaryAbstract::kSplitText = "<br>";

DictionaryAbstract::DictionaryAbstract() { }

DictionaryAbstract::~DictionaryAbstract() { }

// ================================

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

QVector<int> DictionaryAbstract::Search(const EntryAbstract &entry) {
    QVector<int> vec_index;
	for (int i = 0; i < entries_.size(); i++) {
        if (entries_[i] == entry)
            vec_index.push_back(i);
	}
    return vec_index;
}

// ================================

int DictionaryAbstract::Size() {
    return entries_.size();
}

EntryAbstract DictionaryAbstract::Display(const int index) {
    if (index < 0 || entries_.size() <= index)
        throw "WS_DICTIONARY: Invaild Entry Index";
    return entries_[index];
}

// ================================

void DictionaryAbstract::SaveToFile(const QString &str_path) {
    QFile file(str_path);

    QString str_set;
    QString str_tmp;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw "WS_DICTIONARY: Open File Failed";

    for (int n = 0; n < entries_.size(); n++) {
        str_set = "";

        for (int i = 0; i < entries_[n].Size(); i++) { // 末尾带分隔符
            str_tmp = entries_[n].Getter(i);
            str_set += str_tmp + kSplitText;
        }
        str_set += "\n";

        file.write(str_set.toUtf8());
    }

    file.close();

    return;
}

void DictionaryAbstract::ReadFromFile(const QString &str_path) {
    QFile file(str_path);

    QString str_get;
    EntryAbstract* entry;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw "WS_DICTIONARY: Open File Failed";

    QTextStream stream_get(&file);

    while (!stream_get.atEnd()) {
        str_get = stream_get.readLine();
        QStringList str_list = str_get.split(kSplitText);
        entry = new EntryAbstract();

        if (str_get.size() != 0) {
            for (int i = 0; i < str_list.size() - 1; i++) { // 分割后有\n换行符
                entry->Setter(i, str_list[i]);
            }

            entries_.push_back(*entry);
            delete entry;
        }
    }

	file.close();

    return;
}

} // namespace wintersun
