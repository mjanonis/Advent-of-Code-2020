#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <vector>

int main()
{
  std::ifstream input{"day06.in"};
  std::ofstream output{"day06-2.out"};

  std::string tmp;
  std::set<char> dclr;
  std::vector<std::set<char>> declarations;

  size_t sum = 0;
  while (std::getline(input, tmp)) {
    for (char x : tmp) {
      dclr.insert(x);
    }
    if (!dclr.empty()) {
      declarations.push_back(dclr);
    }
    dclr.clear();

    if (tmp.length() == 0) {
      std::set<char> intersection = declarations[0];
      std::set<char> ci;

      for (size_t i = 1; i < declarations.size(); ++i) {
        std::set_intersection(intersection.begin(), intersection.end(),
                              declarations[i].begin(), declarations[i].end(),
                              std::inserter(ci, ci.begin()));
        std::swap(intersection, ci);
        ci.clear();
      }
      sum += intersection.size();
      declarations.clear();
    }
  }

  // Deal with the last entry
  std::set<char> intersection = declarations[0];
  std::set<char> ci;

  for (size_t i = 1; i < declarations.size(); ++i) {
    std::set_intersection(intersection.begin(), intersection.end(),
                          declarations[i].begin(), declarations[i].end(),
                          std::inserter(ci, ci.begin()));
    std::swap(intersection, ci);
    ci.clear();
  }
  sum += intersection.size();
  declarations.clear();
  output << sum << std::endl;
}
