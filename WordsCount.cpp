#include "WordsCount.h"

int
InVector(char ch, const std::vector<char>& vec)
{
    for(const auto& sus : vec) {
        if (sus == ch)
            return 1;
    }
    return 0;
}

std::string
WordsCount::read_file(const std::string& path)
{
    std::ifstream f(path);
    if (!f)
        std::cerr << "Error! Cannot open a file." << std::endl;
    std::stringstream ss;
    ss << f.rdbuf();
    text = ss.str();

    f.close();
    return text;
}

std::string
WordsCount::erase_separator()
{
    int flagDoubleSpaceHyphen = 0;
    for(const auto& sym : text) {
        if (!InVector(sym, separators) || (sym == '-' && flagDoubleSpaceHyphen == 0)) {
            if ((flagDoubleSpaceHyphen == 0 && sym == ' ') || (sym != ' '))
                cleanText.push_back(sym);
        }
        if (sym == '-' || sym == ' ') {
            flagDoubleSpaceHyphen = 1;
        } else {
            flagDoubleSpaceHyphen = 0;
        }
        if (InVector(sym, sepsToSpaces)) {
            cleanText.push_back(' ');
        }
    }
    for (std::string::iterator it = cleanText.begin(); it != cleanText.end(); it++)
    {
        std::string::iterator begin = it;
        while (it != cleanText.end() && ::isspace(*it) )it++;
        if (it - begin > 1)
            it = cleanText.erase(begin + 1, it) - 1;
    }

    cleanText.push_back('\n');
    return cleanText;
}

std::map<std::string, int>
WordsCount::counter()
{
    std::string word;
    int flagDoubleSpace = 0;
    for(const auto& letter : cleanText) {
        if ((letter == ' ' && flagDoubleSpace == 0) || letter == '\n') {
            check_exist(word);
            word = "";
            flagDoubleSpace = 1;

        }
        else if (letter != ' '){
            word += letter;
            flagDoubleSpace = 0;
        }
    }
    //check_exist(word);

    return mapWordFreq;
}

void
WordsCount::check_exist(const std::string& word)
{
    std::vector<std::string> vec = stopwords_vector();
    if (std::find(vec.begin(), vec.end(), word) != vec.end()) {

    }
    else {

        if (mapWordFreq.find(word) != mapWordFreq.end()) {
            mapWordFreq[word]++;
        } else {
            mapWordFreq[word] = 1;
        }
    }
}

std::vector<std::string>
WordsCount::stopwords_vector()
{
    std::string pathStopWordsFile = "stop-words.txt";
    char delimiter = ',';
    std::string noNeedWords = read_file(pathStopWordsFile);
    std::vector<std::string> noNeedWordsVector;
    size_t pos;
    std::string token;
    while((pos = noNeedWords.find(delimiter)) != std::string::npos) {
        token = noNeedWords.substr(0, pos);
        noNeedWordsVector.push_back(token);
        noNeedWords.erase(0, pos + 1); // + 1, т.к. ','
    }

    return noNeedWordsVector;
}