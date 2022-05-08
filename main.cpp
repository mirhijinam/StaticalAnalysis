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
    setlocale(LC_ALL, "");
    std::string pathMainFile = "x_shakespeare-text.txt";
    WordsCount wordsCount;

    std::ofstream outputBenchmark;
    outputBenchmark.open("x_benchmark.txt");
    if (!outputBenchmark.is_open()) {
        std::cerr << "Error! Cannot open an outfile of benchmarks." << std::endl;
    }
    auto t1ReadFile = high_resolution_clock::now();
    std::wstring originalText = wordsCount.read_file(pathMainFile); // // // // // // // // // //
    auto t2ReadFile = high_resolution_clock::now();
    auto msReadFile_int = duration_cast<milliseconds>(t2ReadFile - t1ReadFile);
    duration<double, std::milli> msReadFile_double = t2ReadFile - t1ReadFile;
    outputBenchmark << "Benchmark for file reading: " << msReadFile_double.count() << "ms" << std::endl;

    outputBenchmark.close();

    std::wofstream outputTerminal;
    outputTerminal.open("y_original-and-clean-texts.txt", std::ios::out | std::ios::binary);
    if (!outputTerminal.is_open())
        std::cerr << "Error! Cannot open an outfile of texts." << std::endl;
    outputTerminal.imbue(std::locale(outputTerminal.getloc(),new std::codecvt_utf8_utf16<wchar_t>));
    outputTerminal << L"до:" << std::endl;
    for (auto wcharFromOrigText : originalText) {
        outputTerminal << wcharFromOrigText;
    }
    outputTerminal << std::endl;

    std::wstring cleanText;
    cleanText = wordsCount.erase_separator();
    outputTerminal << L"\nпосле:" << std::endl;
    for (auto wcharFromCleanText : cleanText) {
        outputTerminal << wcharFromCleanText;
    }
    outputTerminal << std::endl;

    outputTerminal.close();


    outputBenchmark.open("x_benchmark.txt", std::wios::app);

    auto t1Counter = high_resolution_clock::now();
    std::map<std::wstring, int> count = wordsCount.counter(); // // // // // // // // // //
    auto t2Counter = high_resolution_clock::now();
    auto msCounter_int = duration_cast<milliseconds>(t2Counter - t1Counter);
    duration<double, std::milli> msCounter_double = t2Counter - t1Counter;
    outputBenchmark << "Benchmark for counting: " << msCounter_double.count() << "ms" << std::endl;

    outputBenchmark.close();

    SortPrintMap(count);

    return 0;
}