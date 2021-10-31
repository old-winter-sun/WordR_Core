#ifndef WS_DICTIONARY_H_
#define WS_DICTIONARY_H_

#include <QString>
#include <QVector>
#include "ws_error.h"
#include "ws_entry.h"

// 考虑到cmd无法在utf8下输入中文，后续调试已弃用

namespace wintersun
{

constexpr std::streamsize kMaxReadSize = 1024;

class DictionaryAbstract
{
public:
	DictionaryAbstract();
	virtual ~DictionaryAbstract();

	virtual Result Add(const EntryAbstract&);
	virtual Result Delete(const int);
    virtual Result Revise(const int, const EntryAbstract&);                 // 以后添加正则表达式
    virtual Result Search(const EntryAbstract&, QVector<int>& index_out);	// 目前全匹配查找entry_in里非空元素

    virtual Result Size(int& size_out);
	virtual Result Display(const int, EntryAbstract& entry_out);

    virtual Result SaveToFile(const QString&);
    virtual Result ReadFromFile(const QString&);

    static const int kMaxElementNum = EntryAbstract::kMaxElementNum;

private:
    QVector<EntryAbstract> entries_;

    static const QString kIdentifier;
};

} // namespace wintersun

#endif // !WS_DICTIONARY_H_
