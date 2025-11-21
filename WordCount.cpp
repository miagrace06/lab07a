// WordCount.cpp

#include "WordCount.h"
#include "tddFuncs.h"
using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int total = 0;
	for (size_t i = 0; i < CAPACITY; i++) {
		for (const auto& entry: table[i]) {
			total += entry.second;
		}
	}
	return total;
}

int WordCount::getNumUniqueWords() const {
	int total = 0;
	for (size_t i = 0; i < CAPACITY; i ++) {
		total += table[i].size();
	}
	return total;
}

int WordCount::getWordCount(std::string word) const {
	word = makeValidWord(word);

	if (word == "") {
		return 0;
	}
	size_t index = hash(word);
	for (const auto& entry : table[index]) {
		if (entry.first == word) {
			return entry.second;
		}
	}
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	word = makeValidWord(word);

	if (word == "") {
		return 0;
	}
	size_t index = hash(word);
	for (auto& entry : table[index]) {
		if (entry.first == word) {
			entry.second++;
			return entry.second;
		}
	}
	table[index].push_back(std::make_pair(word, 1));
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	word = makeValidWord(word);
	if (word == "") {
		return -1;
	}
	size_t index = hash(word);
	auto& vec = table[index];

	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i].first == word) {
			int count = vec[i].second;
			if (count > 1) {
				vec[i].second--;
				return vec[i].second;
			}else if (count == 1) {
				vec.erase(vec.begin() + i);
				return 0;
			}else {
				return -1;
			}
		}
	}
	return -1;
}

bool WordCount::isWordChar(char c) {
	if (isalpha(c)) {
		return true;
	}else {
		return false;
	}
}

std::string WordCount::makeValidWord(std::string word) {
	std::string result;

	for (size_t i = 0; i < word.size(); i++) {
		char c = std::tolower(word[i]);

		if (isWordChar(c)) {
			result += c;
		}else if ((c == '-' || c == '\'') && !result.empty() && i + 1 < word.size()) {
			result += c;
		}else {

		}
	}
	while (!result.empty() && !isWordChar(result.front())) {
		result.erase(result.begin());
	}
	while (!result.empty() && !isWordChar(result.back())) {
		result.pop_back();
	}
	return result;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> allWords;

	for (size_t i = 0; i < CAPACITY; i++) {
		for (const auto& entry: table[i]) {
			allWords.push_back(entry);
		}
	}
	std::sort(allWords.begin(), allWords.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
			return a.first > b.first;
			}
		 );
	for (const auto &entry : allWords) {
		out << entry.first << "," << entry.second << "\n";
	}
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> allWords;

	for (size_t i = 0; i < CAPACITY; i++) {
		for (const auto& entry : table[i]) {
			allWords.push_back(entry);
		}
	}
	std::sort(allWords.begin(), allWords.end(),[](const std::pair<std::string,int> &a, const std::pair<std::string,int> &b) {
			if (a.second != b.second) {
				return a.second < b.second;
			}
			return a.first < b.first;
		}
	);
	for(const auto& entry : allWords) {
		out << entry.first << "," << entry.second<< "\n";
	}
}
void WordCount::addAllWords(std::string text) {
	std::string current;

	for (char c : text) {
		if (isalpha(c)) {
			current += std::tolower(c);
		}else {
			if (!current.empty()) {
				incrWordCount(current);
				current.clear();
			}
		}
	}
	if (!current.empty()) {
		incrWordCount(current);
	}
}
