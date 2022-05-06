#ifndef STATISTICALANALYSIS_SORTPRINTMAP_H
#define STATISTICALANALYSIS_SORTPRINTMAP_H



void
SortPrintMap(std::map<std::wstring, int> const& m)
{
    std::vector<std::pair<std::wstring, int>> vec;
    vec.reserve(m.size()); // ????????????????????
    for (const auto &item : m) {
        vec.emplace_back(item);
    }

    std::sort(vec.begin(), vec.end(),
              [] (const std::pair<std::wstring, int> &x, const std::pair<std::wstring, int> &y){
                  return x.second > y.second;
              });

    std::wofstream out;
    out.open("x_stats.txt");
    if (!out.is_open())
    {
        std::cerr << "Error! Cannot open an outfile." << std::endl;
    }
    for (auto const &pair: vec) {
        out << pair.first << " : " << pair.second << std::endl;
    }

    out.close();
}



#endif //STATISTICALANALYSIS_SORTPRINTMAP_H