#ifndef WS_ENTRY_H_
#define WS_ENTRY_H_

// 头文件仅输出有变量名带后缀_out，且位于函数参数末尾

// Qt的代码后面换成Boost的

#include <QString>
#include "ws_error.h"

namespace wintersun
{

class EntryAbstract
{
public:
	static const int kMaxElementNum = 2;

	EntryAbstract();
    EntryAbstract(const QString&, const QString&);
	virtual ~EntryAbstract();

    virtual Result Getter(const int, QString& str_out) const;
    virtual Result Setter(const int, const QString&);

	bool operator==(const EntryAbstract&);

private:
    QString writing_;
    QString meaning_;
};

} // namespace wintersun

#endif // !WS_ENTRY_H_
