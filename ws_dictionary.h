#ifndef WS_DICTIONARY_H_
#define WS_DICTIONARY_H_

#include <QSharedPointer>
#include <QString>
#include <QVector>
#include "ws_entry.h"

namespace wintersun
{

//constexpr std::streamsize kMaxReadSize = 1024;

// 基本字典
class DictionaryBase {
public:
    DictionaryBase() { };
    virtual ~DictionaryBase() { };

    // 操作
    void         Add(QSharedPointer<EntryAbstract>&);               // 增加
    void         Delete(const int);                                 // 删除
    void         Revise(const int, QSharedPointer<EntryAbstract>&); // 修改
    QVector<int> Search(const QString&);                            // 查找

    // 信息
    int            Size();                   // 词条个数
    const EntryAbstract& Display(const int); // 词条输出

    // 文件流
    void SaveToFile(const QString&);   // 文件保存
    void ReadFromFile(const QString&); // 文件读取

private:
    QVector<QSharedPointer<EntryAbstract>> p_entries_; // 词条指针

    static const QString kSplitEntry; // 标识符：对应一个词条
};

} // namespace wintersun

#endif // !WS_DICTIONARY_H_
