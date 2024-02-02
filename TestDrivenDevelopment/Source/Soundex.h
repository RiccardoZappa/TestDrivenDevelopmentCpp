#pragma once
#include <string>
#include <unordered_map>

static const size_t MaxWordLength{ 4 };
const std::string NotADigit{ '*' };

class Soundex
{
public:
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
	std::string Head(const std::string& word) const
	{
		return word.substr(0, 1);
	}

	std::string tail(const std::string& word) const 
	{
		return word.substr(1);
	}

	std::string EncodedDigits(const std::string& word) const
	{
		std::string encoding;
		EncodeHead(encoding, word);
		EncodeTail(encoding, word);
		return encoding;
	
	}

	std::string ZeroPad(const std::string& word) const
	{
		auto ZerosNeeded = MaxWordLength - word.length();
		return word + std::string(ZerosNeeded, '0');
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

	std::string UpperFront(const std::string& string) const
	{
		return std::string(1, std::toupper(static_cast<unsigned char>(string.front())));
	}

	char Lower(char c) const
	{
		return std::tolower(static_cast<unsigned char>(c));
	}

	void EncodeHead(std::string& encoding, const std::string& word) const
	{
		encoding += EncodedDigit(word.front());
	}

	void EncodeTail(std::string& encoding, const std::string& word) const
	{
		for (auto letter : tail(word))
		{
			if (isComplete(encoding)) break;

			auto digit = EncodedDigit(letter);
			if (digit != NotADigit && digit != LastDigit(encoding))
				encoding += digit;
		}
	}
};