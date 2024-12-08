#pragma once

#if defined(DLL_NO_EXPORT)
#define LAMP_API
#elif defined(DLL_EXPORT_Lamp)
#define LAMP_API __declspec(dllexport)
#else
#define LAMP_API __declspec(dllimport)
#endif
