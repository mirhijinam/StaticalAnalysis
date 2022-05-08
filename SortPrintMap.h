#ifndef STATISTICALANALYSIS_SORTPRINTMAP_H
#define STATISTICALANALYSIS_SORTPRINTMAP_H
#include <clocale>


void
SortPrintMap(std::map<std::wstring, int> const& m)
{
    setlocale(LC_ALL, "");
    std::vector<std::pair<std::wstring, int>> vec;
    vec.reserve(m.size()); // ????????????????????
    for (const auto &item : m) {
        vec.emplace_back(item);
    }

    std::sort(vec.begin(), vec.end(),
              [] (const std::pair<std::wstring, int> &x, const std::pair<std::wstring, int> &y){
                  return x.second > y.second;
              });


    std::wofstream out("y_stats.txt", std::ios::out | std::ios::binary);
    if (!out.is_open())
    {
        std::cerr << "Error! Cannot open an outfile." << std::endl;
    }
    out.imbue(std::locale(out.getloc(),new std::codecvt_utf8_utf16<wchar_t>)); //idk what is it but it's work
    for (auto const &pair: vec)
        out << pair.first << L" : " << pair.second << std::endl;
    out.close();

}



#endif //STATISTICALANALYSIS_SORTPRINTMAP_H