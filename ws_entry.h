#ifndef WS_ENTRY_H_
#define WS_ENTRY_H_

#include <QString>
#include <QVector>

namespace wintersun
{

class EntryAbstract {
public:
	EntryAbstract();
    EntryAbstract(const QString &, const QString &);
	virtual ~EntryAbstract();

    // 获取修改等 从 1 开始
    virtual QString Getter(const int) const;
    virtual void    Setter(const int, const QString &);  // 正索增引加或修改，负索引删除
    virtual int     Size();                             // 返回大小(元素个数)

    // 运算符
    bool operator==(const EntryAbstract &);

private:
    QString writing_;
    QVector<QString> definitions_;
};

//class EntryStandardEN : public EntryAbstract

} // namespace wintersun

#endif // !WS_ENTRY_H_
