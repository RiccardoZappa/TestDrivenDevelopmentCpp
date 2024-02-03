#pragma once
#include<string>

namespace Utils
{
	namespace CharUtil
	{
		char Lower(char c)
		{
			return std::tolower(static_cast<unsigned char>(c));
		}

		bool isVowel(char letter)
		{
			return std::string("aeiouy").find(Lower(letter)) != std::string::npos;
		}
	}
}
