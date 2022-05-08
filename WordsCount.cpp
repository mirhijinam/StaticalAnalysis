#include "WordsCount.h"
#include <regex>
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
    std::string strText;
    std::ifstream f(path);
    if (!f)
        std::cerr << "Error! Cannot open a file." << std::endl;
    std::stringstream ss;
    ss << f.rdbuf();
    strText = ss.str();
    f.close();
    std::wstring_convert <std::codecvt_utf8 <wchar_t>, wchar_t> convert;
    text = convert.from_bytes(strText);
    return text;
}

std::wstring
WordsCount::erase_separator()
{
    int flagDoubleSpaceHyphen = 0;

    for(auto wchar : text) {
        if (!InVector(wchar, separators) || (wchar == L'-' && flagDoubleSpaceHyphen == 0)) {
            if ((flagDoubleSpaceHyphen == 0 && wchar == L' ') || (wchar != L' '))
                cleanText += wchar;
        }
        if (wchar == L'-' || wchar == L' ') {
            flagDoubleSpaceHyphen = 1;
        } else {
            flagDoubleSpaceHyphen = 0;
        }
        if (InVector(wchar, sepsToSpaces)) {
            cleanText += L' ';
        }
    }
    reduce(cleanText);
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

std::wstring
WordsCount::trim(const std::wstring& str,
                 wchar_t space_trim)
{
    const auto strBegin = str.find_first_not_of(space_trim);
    if (strBegin == std::string::npos)
        return L""; // no content

    const auto strEnd = str.find_last_not_of(space_trim);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::wstring
WordsCount::reduce(const std::wstring& str,
                   const std::wstring& fill,
                   wchar_t space)
{
    // trim first
    auto result = trim(str, space);

    // replace sub ranges
    auto beginSpace = result.find_first_of(space);
    while (beginSpace != std::wstring::npos)
    {
        const auto endSpace = result.find_first_not_of(space, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(space, newStart);
    }
    cleanText = result;
    return cleanText;
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