#ifndef WS_DICTIONARY_H_
#define WS_DICTIONARY_H_

#include <QString>
#include <QVector>
#include "ws_entry.h"

namespace wintersun
{

constexpr std::streamsize kMaxReadSize = 1024;

class DictionaryAbstract {
public:
    DictionaryAbstract();
    virtual ~DictionaryAbstract();

    // 操作
    virtual void         Add(const EntryAbstract &);               // 增加
    virtual void         Delete(const int);                        // 删除
    virtual void         Revise(const int, const EntryAbstract &); // 修改
    virtual QVector<int> Search(const QString &);                  // 查找

    // 信息
    virtual int           Size();             // 词条个数
    virtual EntryAbstract Display(const int); // 词条输出

    // 文件流
    virtual void SaveToFile(const QString &);   // 文件保存
    virtual void ReadFromFile(const QString &); // 文件读取

private:
    QVector<EntryAbstract> entries_;

    static const QString kSplitEntry; // 标识符：对应一个词条
};

} // namespace wintersun

#endif // !WS_DICTIONARY_H_
