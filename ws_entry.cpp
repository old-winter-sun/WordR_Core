#include "ws_entry.h"

namespace wintersun
{

// 0 拼写；1 ~ n 含义
QString EntryAbstract::Getter(const int index) const{
    if (index == 0)
        return writing_;
    if (index < 0 || meanings_.size() < index)
        throw "WS_ENTRY Getter(int): Element Index Negative Or Too Large";
    return meanings_[index - 1];
}

// 正索引：新增或修改，负索引：删除
void EntryAbstract::Setter(const int index, const QString &str) {
    if (index == 0)
        writing_ = str;
    else if (meanings_.size() < index)
        meanings_.push_back(str);
    else if (0 < index && index <= meanings_.size())
        meanings_.insert(meanings_.constBegin() + index - 1, str);
    else if (-meanings_.size() <= index && index < 0)
        meanings_.erase(meanings_.constBegin() - index - 1);
    else
        throw "WS_ENTRY Setter(int): Element Index Too Small Negative Number";
}

// 最小为 1，仅含writing_
int EntryAbstract::Size() {
    return meanings_.size() + 1;
}

} // namespace wintersun
