#include "ws_error.h"

namespace wintersun
{

Result::Result() {
    ifsuccess = true;
    error[0] = '\0';
}

Result::Result(const char* p_sz) { // 规定sz为char[]型数组字符串，str为string类字符串
	ifsuccess = false;
	error[0] = '\0';

	for (int i = 0; i < error_size && *(p_sz + i) != '\0'; i++) {
		error[i] = *(p_sz + i);
	}
}

} // namespace wintersun
