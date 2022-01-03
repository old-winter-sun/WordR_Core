#ifndef WS_ENTRY_H
#define WS_ENTRY_H

#include <QString>
#include <QVector>

namespace wintersun {

// 抽象词条
// 将所有成员变量看作元素，按照先后顺序用数字索引
// 若有一个元素为可变大小集合，将其置于末尾
// 不应存在多个可变大小的元素
class EntryAbstract {
public:
    EntryAbstract() { };
    virtual ~EntryAbstract() { };

    virtual QString Get(const int) const = 0;           // 获取
    virtual void    Add(const QString&) = 0;            // 增加
    virtual void    Delete(const int) = 0;              // 删除
    virtual void    Set(const int, const QString&) = 0; // 修改

    virtual int     Match(const QString&) const = 0;    // 匹配
    virtual int     Size() const = 0;                   // 大小
    virtual QString Type() const = 0;                   // 类型
};

// 自由词条
// 该词语的书写 + 装饰（含义，拼读等）
// 当文件未标注词条属性时采用
class EntryFree : public EntryAbstract {
public:
    EntryFree() { };
    EntryFree(const QString& str): writing_(str) { };
    ~EntryFree() { };

    QString Get(const int) const;
    void    Add(const QString&);
    void    Delete(const int);
    void    Set(const int, const QString&);

    int     Match(const QString&) const;
    int     Size() const;
    QString Type() const;

private:
    QString writing_;              // 书写
    QVector<QString> decorations_; // 装饰

    static const QString kEntryType; // 标识符：词条类型
};

} // namespace wintersun

#endif // !WS_ENTRY_H
