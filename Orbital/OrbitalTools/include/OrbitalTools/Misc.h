#pragma once

#include "OrbitalTools/Errors.h"

namespace Orbital
{
	static inline auto SplitString(const std::string& toSplit, char delimiter = ' ')
		-> std::vector<std::string>
	{
		std::vector<std::string> result;
		std::stringstream stream(toSplit);
		std::string item;

		while (std::getline(stream, item, delimiter))
		{
			result.push_back(item);
		}

		return result;
	}

	static inline auto ToInteger(const std::string& string) -> Option<unsigned int>
	{
		size_t count = std::count_if(string.begin(), string.end(), [](char v) { return std::isdigit(v); });

		return count == string.size() ? std::stoi(string) : Option<unsigned int>{};
	}

	static inline auto IncrementString(std::string& toIncrement) -> void
	{
		std::vector<std::string> words = SplitString(toIncrement);
		std::string lastWord = *(words.end() - 1);

		Option<unsigned int> integer = ToInteger(lastWord);

		if (integer)
		{
			lastWord = std::to_string(*integer + 1);
			toIncrement = "";
			
			for (auto wordIt = words.begin(); wordIt != words.end() - 1; wordIt++)
			{
				toIncrement += *wordIt + " ";
			}
			
			toIncrement += lastWord;
		}
		else
		{
			toIncrement = toIncrement + " 2";
		}
	}
} // namespace Orbital
