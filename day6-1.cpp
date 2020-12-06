#include <fstream>
#include <set>
#include <string>
#include <vector>

int main()
{
  std::ifstream input{"day6.in"};
  std::ofstream output{"day6-1.out"};

  std::string tmp;
  std::set<char> dclr;

  size_t sum = 0;
  while (std::getline(input, tmp)) {
    for (char x : tmp) {
      dclr.insert(x);
    }

    if (tmp.length() == 0) {
      sum += dclr.size();
      dclr.clear();
    }
  }

  // Deal with the last entry
  sum += dclr.size();

  output << sum << std::endl;
}
