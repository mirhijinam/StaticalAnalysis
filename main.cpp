#include "WordsCount.h"
#include "SortPrintMap.h"

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

int
main(int argc, char** argv)
{
    std::string pathMainFile = "shakespeare-text.txt";
    WordsCount wordsCount;

    auto t1ReadFile = high_resolution_clock::now();
    std::string originalText = wordsCount.read_file(pathMainFile); // // // // // // // // // //
    auto t2ReadFile = high_resolution_clock::now();
    auto msReadFile_int = duration_cast<milliseconds>(t2ReadFile - t1ReadFile);
    duration<double, std::milli> msReadFile_double = t2ReadFile - t1ReadFile;
    std::cout << "Benchmark for file reading:" << std::endl;
    std::cout << msReadFile_int.count() << "ms\n";
    std::cout << msReadFile_double.count() << "ms\n";

    std::cout << "\nдо:\n" << "\"" << originalText << "\"" << std::endl;
    std::string cleanText;
    cleanText = wordsCount.erase_separator();
    std::cout << "\nпосле:\n" << "\"" <<cleanText.substr(0, cleanText.length()-1) << "\"\n" << std::endl;

    auto t1Counter = high_resolution_clock::now();
    std::map<std::string, int> count = wordsCount.counter(); // // // // // // // // // //
    auto t2Counter = high_resolution_clock::now();
    auto msCounter_int = duration_cast<milliseconds>(t2Counter - t1Counter);
    duration<double, std::milli> msCounter_double = t2Counter - t1Counter;
    std::cout << "Benchmark for counting:" << std::endl;
    std::cout << msCounter_int.count() << "ms\n";
    std::cout << msCounter_double.count() << "ms\n";

    SortPrintMap(count);

    return 0;
}