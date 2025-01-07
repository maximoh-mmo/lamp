#pragma once
#include <bitset>

using Entity = uint32_t;
constexpr Entity MAX_ENTITIES = 50;

using ComponentType = uint8_t;
constexpr ComponentType MAX_COMPONENTS = 16;

using Signature = std::bitset<MAX_COMPONENTS>;