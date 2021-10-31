#include "ws_dictionary.h"

#include <QFile>
#include <QTextStream>

namespace wintersun {

const QString DictionaryAbstract::kIdentifier = "&nbsp;";

DictionaryAbstract::DictionaryAbstract() {
}

DictionaryAbstract::~DictionaryAbstract() {
}

Result DictionaryAbstract::Add(const EntryAbstract& entry) {
	entries_.push_back(entry);

	return Result();
}

Result DictionaryAbstract::Delete(const int index) {
    entries_.remove(1, index);

	return Result();
}

Result DictionaryAbstract::Revise(const int index, const EntryAbstract& entry) {
	entries_[index] = entry;

	return Result();
}

Result DictionaryAbstract::Search(const EntryAbstract& entry_in, QVector<int>& index_out) {
	for (int i = 0; i < entries_.size(); i++) {
		if (entries_[i] == entry_in)
			index_out.push_back(i);
	}

	return Result();
}

Result DictionaryAbstract::Size(int& size_out) {
	size_out = entries_.size();

	return Result();
}

Result DictionaryAbstract::Display(const int index, EntryAbstract& entry_out) {
	entry_out = entries_[index];

	return Result();
}

Result DictionaryAbstract::SaveToFile(const QString& str_path) {
    QFile file(str_path);

    QString str_set;
    QString str_tmp;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return Result("Open file failed");

    for (int n = 0; n < entries_.size(); n++) {
        str_set = "";

        for (int i = 0; i < kMaxElementNum - 1; i++) {
            entries_[n].Getter(i, str_tmp);
            str_set += str_tmp + kIdentifier;
        }
        entries_[n].Getter(kMaxElementNum, str_tmp);
        str_set += str_tmp; // 末尾不需要标识符

        file.write(str_set.toUtf8());
    }

    file.close();

    return Result();
}

Result DictionaryAbstract::ReadFromFile(const QString& str_path) {
    QFile file(str_path);

    QString str_get;
    EntryAbstract entry;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return Result("Open file failed");

    QTextStream stream_get(&file);

    while (!stream_get.atEnd()) {
        str_get = stream_get.readLine();
        QStringList str_list = str_get.split(kIdentifier);

        if (str_get.size() != 0) {
            for (int i = 0; i < str_list.size() && i < kMaxElementNum; i++) {
                entry.Setter(i, str_list[i]);
            }

            entries_.push_back(entry);
        }
    }

	file.close();

	return Result();
}

} // namespace wintersun
