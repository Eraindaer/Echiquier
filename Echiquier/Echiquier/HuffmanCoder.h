#pragma once
#include <string>
#include <algorithm>
#include <map>

class HuffmanCoder
{
public:
	HuffmanCoder();
	~HuffmanCoder();

	std::string Compression(std::string sentence, std::map<char, std::string>& code);
	std::string Decompression(std::string encodedText, std::map<char, std::string> code);

private:
	std::multimap<int, char>        letters;
	std::multimap<int, std::string> tree;
	std::multimap<int, std::string> tree2;
	std::string                     copy;
};

