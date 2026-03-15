#include<iostream>
#include <memory>
template<typename ... Args>
static std::wstring wstr_format(const std::wstring& format, Args ... args)
{
	auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
	std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

	if (!buf)
		return std::wstring("");

	std::snprintf(buf.get(), size_buf, format.c_str(), args ...);
	return std::wstring(buf.get(), buf.get() + size_buf - 1);
}

int main() {
	//std::wstring wstr = wstr_format(L"%.1f", 3.141593);
	std::wstring wstr = wstr_format(L"%d.%d.%d", 2, 3, 2);
	std::wcout << wstr.c_str() << "\n";


	//swprintf_s(tempstr, L"%.1f", p1.GetArea());
}