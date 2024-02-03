#pragma once
#include <string>

namespace Utils
{
	namespace StringUtil
	{
		static const size_t MaxWordLength{ 4 };

		std::string UpperFront(const std::string& string) 
		{
			return std::string(1, std::toupper(static_cast<unsigned char>(string.front())));
		}

		std::string ZeroPad(const std::string& word) 
		{
			auto ZerosNeeded = MaxWordLength - word.length();
			return word + std::string(ZerosNeeded, '0');
		}

		std::string Head(const std::string& word) 
		{
			return word.substr(0, 1);
		}

		std::string tail(const std::string& word) 
		{
			return word.substr(1);
		}

	}
}
