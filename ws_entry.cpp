#include "ws_entry.h"

namespace wintersun
{

EntryAbstract::EntryAbstract() { }

EntryAbstract::EntryAbstract(const QString &str_1, const QString &str_2) :
    writing_(str_1), definitions_(str_2) { }

EntryAbstract::~EntryAbstract() { }

// ================================

QString EntryAbstract::Getter(const int index) const{
    if (index == 0)
        return writing_;
    if (index < 0 || definitions_.size() < index)
        throw "WS_ENTRY Getter(int): Element Index Negative Or Too Large";
    return definitions_[index - 1];
}

void EntryAbstract::Setter(const int index, const QString &str) {
    if (index == 0)
        writing_ = str;
    else if (definitions_.size() < index)
        definitions_.push_back(str);
    else if (0 < index && index <= definitions_.size())
        definitions_.insert(definitions_.constBegin() + index - 1, str);
    else if (-definitions_.size() <= index && index < 0)
        definitions_.erase(definitions_.constBegin() - index - 1);
    else
        throw "WS_ENTRY Setter(int): Element Index Too Small Negative Number";
}

int EntryAbstract::Size() {
    return definitions_.size() + 1;
}

// ================================

bool EntryAbstract::operator==(const EntryAbstract &entry) {
	if (writing_ != entry.writing_)
        return false;
    if (definitions_ != entry.definitions_)
        return false;

	return true;
}

/******************************************************************/

} // namespace wintersun
