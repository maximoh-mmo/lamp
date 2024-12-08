#include "Lamp/utils.h"
#include <codecvt>

namespace Lamp
{
	std::wstring ConvertStringWstring(const std::string& string)
	{
		if (string.empty()) return std::wstring();
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(string);
	}
}