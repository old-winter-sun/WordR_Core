#include "ws_dictionary.h"

#include <QFile>
#include <QTextStream>

namespace wintersun {

// 基本字典
const QString DictionaryBase::kSplitEntry = QChar(0x1D); // 单个词条标识符 = ASCII分组符

// 操作：================================
void DictionaryBase::Add(QSharedPointer<EntryAbstract>& p_entry) {
    p_entries_.push_back(p_entry);
}

void DictionaryBase::Delete(const int i) {
    if (i < 0 || p_entries_.size() <= i)
        throw "wintersun: void DictionaryBase::Delete(const int)：无效索引";
    p_entries_.erase(p_entries_.constBegin() + i);
}

void DictionaryBase::Revise(const int i, QSharedPointer<EntryAbstract>& p_entry) {
    if (i < 0 || p_entries_.size() <= i)
        throw "wintersun: void DictionaryBase::Revise(const int, QSharedPointer<EntryAbstract>&)：无效索引";
    p_entries_[i] = p_entry;
}

// 按匹配查找
QVector<int> DictionaryBase::Search(const QString& str) {
    QVector<int> vec_index;
    for (int i = 0; i < p_entries_.size(); i++) {
        if (p_entries_[i]->Match(str) != -1)
            vec_index.push_back(i);
	}
    return vec_index;
}

// 信息：================================
int DictionaryBase::Size() {
    return p_entries_.size();
}

const EntryAbstract& DictionaryBase::Display(const int i) {
    if (i < 0 || p_entries_.size() <= i)
        throw "wintersun: const EntryAbstract& DictionaryBase::Display(const int)：无效索引";
    return *p_entries_[i];
}

// 文件流：================================
void DictionaryBase::SaveToFile(const QString& str_path) {
    QFile file(str_path);

    QString str_tmp;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw "wintersun: void DictionaryBase::SaveToFile(const QString&)：打开文件失败";

    for (int n = 0; n < p_entries_.size(); n++) {
        file.write((kSplitEntry + "\n").toUtf8());
        for (int i = 0; i < p_entries_[n]->Size(); i++) {
            str_tmp = p_entries_[n]->Get(i) + "\n";
            file.write(str_tmp.toUtf8());
        }
    }

    file.close();

    return;
}

void DictionaryBase::ReadFromFile(const QString& str_path) {
    QFile file(str_path);

    bool is_first(true), is_new(true);
    QString str_get;
    QSharedPointer<EntryAbstract> entry_tmp(new EntryFree);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw "wintersun: void DictionaryBase::ReadFromFile(const QString&)：打开文件失败";

    QTextStream stream_get(&file);

    while (!stream_get.atEnd()) {
        str_get = stream_get.readLine();

        if (str_get == kSplitEntry) {
            if(is_first)
                is_first = false;
            else {
                is_new = true;
                p_entries_.push_back(entry_tmp);
                entry_tmp.reset(new EntryFree);
            }
        }
        else if (!is_first) { // 第一个标识符前的行，视作注释
            if (is_new) { // 第一行为书写，后续行都为装饰，直到下一个新词条
                is_new = false;
                entry_tmp->Set(0, str_get);
            }
            else
                entry_tmp->Add(str_get);
        }
    }
    p_entries_.push_back(entry_tmp); // 推入最后一个
    entry_tmp.clear();

	file.close();

    return;
}

} // namespace wintersun
