#pragma once

#include "windowsinc.h"
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#pragma warning (disable: 4324) // 'struct_name' : structure was padded due to __declspec(align())
#pragma warning (disable: 26812) // The enum type 'enum_name' is unscoped. Prefer 'enum class' over 'enum'

#ifdef TARGET_DEBUG
#pragma warning (disable: 4100)
#pragma warning (disable: 4189)
#endif