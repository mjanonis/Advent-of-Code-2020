#include <fstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream input{"day03.in"};
  std::ofstream output{"day03-2.out"};

  std::vector<std::string> map;
  std::string tmp;
  std::vector<size_t> tree_counts;

  while (std::getline(input, tmp)) {
    map.push_back(tmp);
  }

  unsigned long tc1 = 0, tc2 = 0, tc3 = 0, tc4 = 0, tc5 = 0;
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0;

  // All down 1
  for (size_t i = 1; i < map.size(); ++i) {
    x1 += 1;
    x1 %= map[0].length();

    x2 += 3;
    x2 %= map[0].length();

    x3 += 5;
    x3 %= map[0].length();

    x4 += 7;
    x4 %= map[0].length();

    if (map[i].at(x1) == '#') {
      ++tc1;
    }
    if (map[i].at(x2) == '#') {
      ++tc2;
    }
    if (map[i].at(x3) == '#') {
      ++tc3;
    }
    if (map[i].at(x4) == '#') {
      ++tc4;
    }
  }

  // Right 1, down 2
  for (size_t i = 2; i < map.size(); i += 2) {
    x5 += 1;
    x5 %= map[0].length();
    if (map[i].at(x5) == '#') {
      ++tc5;
    }
  }

  output << tc1 * tc2 * tc3 * tc4 * tc5 << std::endl;
}
