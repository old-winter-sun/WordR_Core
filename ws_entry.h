#ifndef WS_ENTRY_H_
#define WS_ENTRY_H_

#include <QString>
#include <QVector>

namespace wintersun
{

class EntryAbstract {
public:
    inline EntryAbstract() { };
    inline virtual ~EntryAbstract() { };

    // 索引：0 - writing_ ; 1 ~ n - meanings_
    virtual QString Getter(const int) const;            // 获取
    virtual void    Setter(const int, const QString &); // 修改
    virtual int     Size();                             // 大小

private:
    QString writing_;           // 书写
    QVector<QString> meanings_; // 含义
};

} // namespace wintersun

#endif // !WS_ENTRY_H_
