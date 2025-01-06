#include "utils.h"
#include <codecvt>
#include <cstdarg>


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
        std::mt19937 rng(rd());
        std::uniform_int_distribution<> uni(0, max);
        return uni(rng);
    }

    int RandIntRange(int max, int min)
    {
        std::mt19937 rng(rd());
        std::uniform_int_distribution<> uni(min, max);
        return uni(rng);
    }

     void LogInternal(const char* file, const char* function, uint32_t line, LAMP_LOGCategory category, const char* fmt, ...)
    {
        const char* categoryStr = "";
        switch (category)
        {
        case LAMP_LOGCategory::Info:
            categoryStr = "Info";
            break;
        case LAMP_LOGCategory::Warning:
            categoryStr = "Warning";
            break;
        case LAMP_LOGCategory::Error:
            categoryStr = "Error";
            break;
        }

        va_list args;
        va_start(args, fmt);
        printf("[%s] %s:%d %s: ", categoryStr, file, line, function);
        vprintf(fmt, args);
        printf("\n");
        va_end(args);
    }
}
