#pragma once
#include <string>
#include <unordered_map>

#include "..\Utils\CharUtil.h"
#include "..\Utils\StringUtil.h"

using namespace Utils::CharUtil;
using namespace Utils::StringUtil;

class Soundex
{
public:
	static const size_t MaxWordLength{ 4 };

	std::string encode(const std::string& word) const
	{
		return ZeroPad(UpperFront(Head(word)) + tail(EncodedDigits(word)));
	}

	std::string EncodedDigit(char letter) const
	{
		const std::unordered_map<char,std::string> encodings {
			{'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
			{'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"},
						{'s', "2"}, {'x', "2"}, {'z', "2"},
			{'d', "3"}, {'t', "3"},			
			{'l', "4"},
			{'m', "5"}, {'n', "5"},
			{'r', "6"}
		};
		auto it = encodings.find(Lower(letter));
		return it == encodings.end() ? NotADigit : it->second;
	}
private:
	const std::string NotADigit{ '*' };

	std::string EncodedDigits(const std::string& word) const
	{
		std::string encoding;
		EncodeHead(encoding, word);
		EncodeTail(encoding, word);
		return encoding;
	
	}

	bool isComplete(const std::string& encoding) const
	{
		return encoding.length() == MaxWordLength;
	}

	std::string LastDigit(const std::string& encoding) const
	{
		if (encoding.empty()) return NotADigit;
		return std::string(1, encoding.back());
	}

	void EncodeHead(std::string& encoding, const std::string& word) const
	{
		encoding += EncodedDigit(word.front());
	}

	void EncodeTail(std::string& encoding, const std::string& word) const
	{
		for (auto i = 1u; i < word.length(); i++)
		{
			if (!isComplete(encoding))
				EncodeLetter(encoding, word[i], word[i - 1]);
		}
	}

	void EncodeLetter(std::string& encoding, char letter, char lastLetter) const
	{
		auto digit = EncodedDigit(letter);
		if (digit != NotADigit && (digit != LastDigit(encoding) || isVowel(lastLetter)))
			encoding += digit;
	}
};