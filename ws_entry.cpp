#include "ws_entry.h"

namespace wintersun
{

// 自由词条
// 0 书写；1 ~ n 装饰

const QString EntryFree::kEntryType = 0; // 自由词条标识符 = 整数 0

// ================================

QString EntryFree::Get(const int i) const {
    if (i == 0)
        return writing_;
    else if (0 < i && i <= decorations_.size())
        return decorations_[i - 1];
    else
        throw "wintersun: QString EntryFree::Get(const int) const：输入的元素索引过大或为负";
}

void EntryFree::Add(const QString& str) {
    decorations_.push_back(str);
}

void EntryFree::Delete(const int i) {
    if (i == 0)
        throw "wintersun: void EntryFree::Delete(const int)：不能删除词语书写";
    else if (0 < i && i <= decorations_.size())
        decorations_.erase(decorations_.constBegin() + i - 1);
    else
        throw "wintersun: void EntryFree::Delete(const int)：输入的元素索引过大或为负";
}

void EntryFree::Set(const int i, const QString& str) {
    if (i == 0)
        writing_ = str;
    else if (0 < i && i <= decorations_.size())
        decorations_[i - 1] = str;
    else
        throw "wintersun: void EntryFree::Set(const int, const QString&)：输入的元素索引过大或为负";
}

// ================================

// 返回首个匹配元素的索引，-1 代表没有
int EntryFree::Match(const QString& str) const {
    if (writing_.indexOf(str) != -1)
        return 0;
    else
        for(int n = 0; n < decorations_.size(); n++) {
            if(decorations_[n].indexOf(str) != -1)
                return n + 1;
        }
    return -1;
}

// 最小为 1，仅含writing_
int EntryFree::Size() const {
    return decorations_.size() + 1;
}

QString EntryFree::Type() const {
    return kEntryType;
}

} // namespace wintersun
