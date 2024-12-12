#pragma once
#include <random>
#include <string>
#include "Lamp_Interface.h"

namespace Lamp
{
	enum class LAMP_LOGCategory
	{
		Info,
		Warning,
		Error
	};
	#ifdef TARGET_DEBUG
	#define LAMP_ASSERTF(condition, fmt, ...) \
		do \
		{ \
			if (!(condition)) \
			{ \
				static bool s_CallAgain = true; \
				if(s_CallAgain && Lamp::AssertInternal(__FILE__, __FUNCTION__, __LINE__, s_CallAgain, #condition, fmt, ##__VA_ARGS__)) \
				{ \
					DebugBreak(); \
				} \
			} \
		} while (0)
	#else
	#define LAMP_ASSERTF(condition, fmt, ...) \
		do \
		{ \
			(void)(condition); \
		} while(0)
	#endif

	#define DISALLOW_COPYING(type) \
		type(const type& other) = delete; \
		type& operator=(const type& other) = delete;

	#define DISALLOW_MOVING(type) \
		type(const type&& other) = delete; \
		type& operator=(const type&& other) = delete;

	#define DISALLOW_MOVE_COPY(type)\
        DISALLOW_COPYING(type)\
        DISALLOW_MOVING(type)

	#define LAMP_STATIC_ASSERT(condition) static_assert(condition, "")

	#define LAMP_LOG(category, fmt, ...) \
		do \
		{ \
			Lamp::LogInternal(__FILE__, __FUNCTION__, __LINE__, category, fmt, ##__VA_ARGS__); \
		} while(0)

	#define LAMP_LOG_INFO(fmt, ...) LAMP_LOG(Lamp::LAMP_LOGCategory::Info, fmt, ##__VA_ARGS__)

	#define LAMP_LOG_WARNING(fmt, ...) LAMP_LOG(Lamp::LAMP_LOGCategory::Warning, fmt, ##__VA_ARGS__)

	#define LAMP_LOG_ERROR(fmt, ...) \
		LAMP_LOG(Lamp::LAMP_LOGCategory::Error, fmt, ##__VA_ARGS__); \
		LAMP_ASSERTF(false, fmt, ##__VA_ARGS__)
	#define LAMP_ASSERT(condition) LAMP_ASSERTF(condition, "")

	LAMP_API std::wstring ConvertStringWstring(const std::string& string);

	LAMP_API void LogInternal(const char* file, const char* function, uint32_t line, LAMP_LOGCategory category, const char* fmt, ...);

	
	static const std::random_device rd;     // Only used once to initialise (seed) engine
    LAMP_API int RandInt(int max);
	LAMP_API int RandIntRange(int max, int min);
}
