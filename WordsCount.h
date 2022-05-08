#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <locale>

#include <codecvt>

#ifndef STATISTICALANALYSIS_WORDSCOUNT_H
#define STATISTICALANALYSIS_WORDSCOUNT_H



class WordsCount {
private:
    std::wstring text;
    std::wstring cleanText;
    std::map<std::wstring, int> mapWordFreq;

public:
    std::wstring read_file(const std::string& path);
    std::wstring erase_separator();
    std::map<std::wstring, int> counter();
    void check_exist(const std::wstring& word);

    std::vector<std::wstring> stopwords_vector();
    std::vector<wchar_t> separators = {L'«',L'»', L'—', L'…', L'.', L'!', L'=', L'?', L',', L';', L':', L'-', L'(', L')', L'[', L']', L'{', L'}', L'\"', L'\'', L'\n', L'\t'};
    std::vector<wchar_t> sepsToSpaces = {L'«',L'»', L'—', L'…', L'(', L')', L'[', L']', L'{', L'}', L'"', L'\'', L'\n', L'\t'};
};



#endif //STATISTICALANALYSIS_WORDSCOUNT_H