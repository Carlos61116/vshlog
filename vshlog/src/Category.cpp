#include "vshlog/Category.h"

namespace vsh
{
	namespace
	{
		std::unordered_map<std::uint32_t, std::string> category{};
	}
	

	void register_category(uint32_t id, const std::string& name)
	{
		category[id] = name;
	}

	std::string_view category_name(uint32_t id)
	{

		if (category.count(id)) 
		{
			return category.at(id);
		}
		else
		{
			return "Unknown";
		}

	}
}