#include "ws_entry.h"

// 输入无后缀，输出后缀_out

namespace wintersun
{

EntryAbstract::EntryAbstract() {
}

EntryAbstract::EntryAbstract(const QString& str_1, const QString& str_2) :
	writing_(str_1), meaning_(str_2) {
}

EntryAbstract::~EntryAbstract() {
}

Result EntryAbstract::Getter(const int element, QString& str_out) const{
	switch (element) {
	case 0:
		str_out = writing_;
		return Result();
	case 1:
		str_out = meaning_;
		return Result();
	default:
		return Result("Invalid element");
	}
}

Result EntryAbstract::Setter(const int element, const QString& str) {
	switch (element) {
	case 0:
		writing_ = str;
		return Result();
	case 1:
		meaning_ = str;
		return Result();
	default:
		return Result("Invalid element");
	}
}

bool EntryAbstract::operator==(const EntryAbstract& entry) {
	if (writing_ != entry.writing_)
		return false;
	if (meaning_ != entry.meaning_)
		return false;

	return true;
}

} // namespace wintersun
