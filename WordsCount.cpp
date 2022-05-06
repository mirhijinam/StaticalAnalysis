#include "WordsCount.h"

int
InVector(wchar_t ch, const std::vector<wchar_t>& vec)
{
    for(wchar_t sus : vec) {
        if (sus == ch)
            return 1;
    }
    return 0;
}

std::wstring
WordsCount::read_file(const std::string& path)
{
    std::wifstream f(path);
    if (!f)
        std::cerr << "Error! Cannot open a file." << std::endl;
    std::wstringstream ss;
    ss << f.rdbuf();
    text = ss.str();
    f.close();
    return text;
}

std::wstring
WordsCount::erase_separator()
{
    int flagDoubleSpaceHyphen = 0;
    for(wchar_t sym : text) {
        if (!InVector(sym, separators) || (sym == L'-' && flagDoubleSpaceHyphen == 0)) {
            if ((flagDoubleSpaceHyphen == 0 && sym == L' ') || (sym != L' '))
                cleanText += sym;
        }
        if (sym == L'-' || sym == L' ') {
            flagDoubleSpaceHyphen = 1;
        } else {
            flagDoubleSpaceHyphen = 0;
        }
        if (InVector(sym, sepsToSpaces)) {
            cleanText += L' ';
        }
    }
    for (std::wstring::iterator it = cleanText.begin(); it != cleanText.end(); it++)
    {
        std::wstring::iterator begin = it;
        while (it != cleanText.end() && ::isspace(*it)) it++;
        if (it - begin > 1)
            it = cleanText.erase(begin + 1, it) - 1;
    }

    cleanText += L'\n';
    return cleanText;
}

std::map<std::wstring, int>
WordsCount::counter()
{
    std::wstring word;
    int flagDoubleSpace = 0;
    for(const auto& letter : cleanText) {
        if ((letter == L' ' && flagDoubleSpace == 0) || letter == L'\n') {
            check_exist(word);
            word = L"";
            flagDoubleSpace = 1;

        }
        else if (letter != L' ') {
            word += letter;
            flagDoubleSpace = 0;
        }
    }

    return mapWordFreq;
}

void
WordsCount::check_exist(const std::wstring& word)
{
    std::vector<std::wstring> vec = stopwords_vector();
    if (std::find(vec.begin(), vec.end(), word) != vec.end()) {

    } else {

        if (mapWordFreq.find(word) != mapWordFreq.end()) {
            mapWordFreq[word]++;
        } else {
            mapWordFreq[word] = 1;
        }
    }
}

std::vector<std::wstring>
WordsCount::stopwords_vector()
{
    std::string pathStopWordsFile = "x_stop-words.txt";
    wchar_t delimiter = L',';
    std::wstring noNeedWords = read_file(pathStopWordsFile);
    std::vector<std::wstring> noNeedWordsVector;
    size_t pos;
    std::wstring token;
    while((pos = noNeedWords.find(delimiter)) != std::wstring::npos) {
        token = noNeedWords.substr(0, pos);
        noNeedWordsVector.push_back(token);
        noNeedWords.erase(0, pos + 1); // + 1, т.к. ','
    }

    return noNeedWordsVector;
}