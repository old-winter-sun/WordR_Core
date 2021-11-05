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

    // 增删改查
    virtual void         Add(const EntryAbstract &);
    virtual void         Delete(const int);
    virtual void         Revise(const int, const EntryAbstract &); // 以后添加正则表达式
    virtual QVector<int> Search(const QString &);                  // 查找相同拼写

    // 操作
    virtual int           Size();             // 词条个数
    virtual EntryAbstract Display(const int); // 输出词条

    // 文件流
    virtual void SaveToFile(const QString &);
    virtual void ReadFromFile(const QString &);

private:
    QVector<EntryAbstract> entries_;

    static const QString kSplitText; // 分隔符
};

} // namespace wintersun

#endif // !WS_DICTIONARY_H_
