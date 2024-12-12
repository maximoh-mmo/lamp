#include "utils.h"
#include <codecvt>

namespace Lamp
{
	std::wstring ConvertStringWstring(const std::string& string)
	{
		if (string.empty()) return std::wstring();
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(string);
	}

    int RandInt(int max)
    {
        std::mt19937 rng(rd);
        std::uniform_int_distribution<int> uni(0, max);
        return uni(rng);
    }

    int RandIntRange(int max, int min)
    {
        std::mt19937 rng(rd);
        std::uniform_int_distribution<int> uni(min, max);
        return uni(rng);
    }
}
