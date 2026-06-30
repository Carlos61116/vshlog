#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

namespace vsh
{
	void register_category(uint32_t id, const std::string& name);

	std::string_view category_name(uint32_t id);
}
