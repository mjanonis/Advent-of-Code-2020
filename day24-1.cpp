#include <fstream>
#include <map>
#include <sstream>

int main()
{
  std::ifstream input{"day24.in"};
  std::ofstream output{"day24-1.out"};

  std::map<int, std::map<int, bool>> black;

  // W, NW, NE, E, SE, SW
  std::map<std::string, int> qd = {{"w", -1}, {"nw", 0}, {"ne", 1},
                                   {"e", 1},  {"se", 0}, {"sw", -1}};
  std::map<std::string, int> rd = {{"w", 0}, {"nw", -1}, {"ne", -1},
                                   {"e", 0}, {"se", 1},  {"sw", 1}};

  std::string tmp;
  while (getline(input, tmp)) {
    int q = 0, r = 0;
    std::istringstream iss(tmp);
    tmp.clear();
    for (char c; iss >> c;) {
      tmp.push_back(c);
      if (c == 's' || c == 'n') {
        continue;
      }
      q += qd[tmp];
      r += rd[tmp];
      tmp.clear();
    }
    black[q][r] = !black[q][r];
  }

  size_t black_tiles = 0;
  for (const auto& q : black) {
    for (const auto& r : q.second) {
      black_tiles += r.second;
    }
  }

  output << black_tiles << std::endl;
}
