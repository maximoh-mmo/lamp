#pragma once

#if defined(TARGET_DEBUG)
#define CONFIG_NAME "Debug"
#elif defined(TARGET_RELEASE)
#define CONFIG_NAME "Release"
#elif defined(TARGET_RETAIL)
#define CONFIG_NAME "Retail"
#endif
