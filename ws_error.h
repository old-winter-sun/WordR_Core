#ifndef WS_ERROR_H_
#define WS_ERROR_H_

namespace wintersun
{

struct Result
{
    static const int error_size = 40;

	bool ifsuccess;
    char error[error_size];

	Result();
	Result(const char*);
};

} // namespace wintersun

#endif // !WS_ERROR_H_
