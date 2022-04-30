#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include <vector>
#include <map>
#include <algorithm>

// Problems:
// Нет русификации
// Считывает \n в конце и в начале текста как отдельный символ
// stopwords_vector() работает только при определении внутри класса

int
InVector(char ch, const std::vector<char>& vec)
{
    for(const auto& sus : vec) {
        if (sus == ch)
            return 1;
    }
    return 0;
}

void print_map(std::map<std::string, int> const& m)
{
    std::vector<std::pair<std::string, int>> vec;
    vec.reserve(m.size()); // ????????????????????
for (const auto &item : m) {
        vec.emplace_back(item);
    }

    std::sort(vec.begin(), vec.end(),
              [] (const std::pair<std::string, int> &x, const std::pair<std::string, int> &y){
        return x.second > y.second;
    });

    for (auto const &pair: vec) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}

class
WordsCount
{
    private:
        std::string text;
        std::string cleanText;
        std::string stopWords;
        std::map<std::string, int> mapWordFreq;

    public:
        std::string read_file(const std::string& path);
        std::string erase_separator();
        std::map<std::string, int> counter();
        void check_exist(const std::string& word);

        std::vector<std::string>
        stopwords_vector()
        {
            std::string pathStopW = "/Users/atabekovibrahim/Workshop/StatisticalAnalysis/stop-words.txt";
            char delimiter = ',';
            std::string noNeedWords = read_file(pathStopW);
            std::vector<std::string> noNeedWordsVector;
            size_t pos = 0;
            std::string token;
            while((pos = noNeedWords.find(delimiter)) != std::string::npos) {
                token = noNeedWords.substr(0, pos);
                noNeedWordsVector.push_back(token);
                noNeedWords.erase(0, pos + 1); // + 1, т.к. ','
            }

            return noNeedWordsVector;
        }
        std::vector<char> separators = {'.', '!', '?', ',', ';', ':', '-', '\n', '\t'};
        std::vector<char> sepsToSpaces = {'\n', '\t'};

};

std::string
WordsCount::read_file(const std::string& path)
{
    std::ifstream fileShakespear(path);
    if (!fileShakespear)
        std::cerr << "Error! Cannot open a file." << std::endl;
    std::stringstream ss;
    ss << fileShakespear.rdbuf();
    text = ss.str();

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
    return cleanText;
}

std::map<std::string, int>
WordsCount::counter()
{
    std::string word;
    int flagDoubleSpace = 0;
    for(const auto& letter : cleanText) {
        if (letter == ' ' && flagDoubleSpace == 0) {
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

void WordsCount::check_exist(const std::string& word)
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

int
main(int argc, char** argv)
{
    std::string pathMainFile = "/Users/atabekovibrahim/Workshop/StatisticalAnalysis/shakespeare-text.txt";
    std::string pathStopWordsFile = "/Users/atabekovibrahim/Workshop/StatisticalAnalysis/stop-words.txt";
    WordsCount wordsCount;
    std::string originalText = wordsCount.read_file(pathMainFile);
    std::cout << originalText << " - до" << std::endl;

    std::string cleanText;
    cleanText = wordsCount.erase_separator();
    std::cout << cleanText << " - после" << std::endl;

    std::map<std::string, int> count = wordsCount.counter();

    print_map(count);
    return 0;
}