#include <iostream>
#include <string>
#include <algorithm>
#include <map>
typedef unsigned int ui;

//Compression
std::string Compression(std::string sentence, std::map<char, std::string> &code) {
	std::string copy = sentence;

	std::multimap <int, char> letters;
	std::multimap <int, std::string> tree;
	std::multimap <int, std::string> tree2;

	std::sort(sentence.begin(), sentence.end());

	int iteration = 1;

	for (ui i = 1; i < sentence.length(); i++) {
		if (sentence[i] == sentence[i - 1]) {
			iteration++;
		}
		else {
			letters.insert(std::make_pair(iteration, sentence[i - 1]));
			iteration = 1;
		}
	}
	letters.insert(std::make_pair(iteration, sentence[sentence.length() - 1]));
	for (auto const& entry : letters) {
		std::string s(1, entry.second);
		tree.insert(std::make_pair(entry.first, s));
		code.insert(std::make_pair(entry.second, ""));
	}

	int finalValue = 0;
	do {
		tree2.clear();
		int iterations = 0, value = 0;
		std::string strLetters = "";
		for (auto const& entry : tree) {
			if (iterations < 2) {
				strLetters += entry.second.c_str();
				value += entry.first;
				for (ui i = 0; i < entry.second.length(); i++) {
					int binaryCode = (iterations == 0);
					code.find(entry.second[i])->second += std::to_string(binaryCode);
				}
			}
			else {
				tree2.insert(std::make_pair(entry.first, entry.second));
			}
			if (iterations == 1) {
				tree2.insert(std::make_pair(value, strLetters));
			}
			iterations++;
		}
		tree.clear();
		for (auto const& entry : tree2) {
			tree.insert(std::make_pair(entry.first, entry.second));
		}
	} while (tree.size() != 1);

	for (auto& entry : code) {
		std::reverse(entry.second.begin(), entry.second.end());
		std::cout << entry.first << " : " << entry.second << "\n";
	}

	std::string encodedText = "";
	for (ui i = 0; i < copy.length(); i++) {
		encodedText += code.find(copy[i])->second;
	}

	return encodedText;
}

//Décompression
std::string Decompression(std::map<char, std::string> code, std::string encodedText) {
	std::string encodedChar = "", decompressedText = "";

	for (ui i = 0; i < encodedText.length(); i++) {
		encodedChar += encodedText[i];
		for (auto& entry : code) {
			if (encodedChar == entry.second) {
				decompressedText += entry.first;
				encodedChar = "";
				break;
			}
		}
	}
	return decompressedText;
}

int main() {
	std::map <char, std::string> huffmannCode;
	std::string sentence;
	std::getline(std::cin, sentence);

	std::string encodedText = Compression(sentence, huffmannCode);

	std::cout << encodedText << "\n";

	std::cout << Decompression(huffmannCode, encodedText);

	return 0;
}