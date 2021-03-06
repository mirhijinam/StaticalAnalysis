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
WordsCount::read_stopfile(const std::string &path)
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
    stopWords = convert.from_bytes(strText);

    return stopWords;
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

    cleanText = std::regex_replace(cleanText, std::wregex(L"^ +| +$|( ) +"), L"$1");
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
WordsCount::stopwords_vector() {
    std::string pathStopWordsFile = "x_stop-words.txt";
    wchar_t delimiter = L',';
    std::wstring noNeedWords = read_stopfile(pathStopWordsFile);
    std::vector<std::wstring> noNeedWordsVector;
    size_t pos;
    std::wstring token;
    while ((pos = noNeedWords.find(delimiter)) != std::wstring::npos) {
        token = noNeedWords.substr(0, pos);
        noNeedWordsVector.push_back(token);
        noNeedWords.erase(0, pos + 1); // + 1, ??.??. ','
    }

    return noNeedWordsVector;
}

std::vector<std::wstring>
WordsCount::participles_search()
{
    std::wstring delimiter = L",;:?.!\n\t";
    std::vector<std::wstring> separatedByCommas;
    size_t pos;
    std::wstring textT = text;
    std::wstring token;
    while ((pos = textT.find_first_of(delimiter)) != std::wstring::npos) {
        token = textT.substr(0, pos);
        if (!token.empty() && token != L" ")
            separatedByCommas.push_back(token);
        textT.erase(0, pos + 1);
    }

    std::ofstream howMuchParticiples("number-of-participles.txt");
    std::wregex participleSuffixes {};
    for (const auto& part : separatedByCommas) {
       howMuchParticiples << std::regex_search(part, participleSuffixes) << std::endl;
    }
    return separatedByCommas;
}