#ifndef STATISTICALANALYSIS_SORTPRINTMAP_H
#define STATISTICALANALYSIS_SORTPRINTMAP_H



void
SortPrintMap(std::map<std::string, int> const& m)
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

std::ofstream out;
out.open("stats.txt");
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
