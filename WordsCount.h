#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#ifndef STATISTICALANALYSIS_WORDSCOUNT_H
#define STATISTICALANALYSIS_WORDSCOUNT_H



class WordsCount {
private:
    std::string text;
    std::string cleanText;
    std::map<std::string, int> mapWordFreq;

public:
    std::string read_file(const std::string& path);
    std::string erase_separator();
    std::map<std::string, int> counter();
    void check_exist(const std::string& word);

    std::vector<std::string> stopwords_vector();
    std::vector<char> separators = {'.', '!', '?', ',', ';', ':', '-', '\n', '\t'};
    std::vector<char> sepsToSpaces = {'\n', '\t'};

};



#endif //STATISTICALANALYSIS_WORDSCOUNT_H
