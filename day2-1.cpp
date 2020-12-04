#include <algorithm>
#include <fstream>
#include <vector>

int main()
{
  std::ifstream input{"day2.in"};
  std::ofstream output{"day2-1.out"};

  std::string tmp;
  unsigned int valid_pwords = 0;

  while (std::getline(input, tmp)) {

    size_t min = std::stoi(tmp.substr(0, tmp.find('-')));
    size_t max = std::stoi(tmp.substr(tmp.find('-') + 1));
    char ch = tmp.at(tmp.find(' ') + 1);

    size_t occur = std::count(tmp.begin() + tmp.find(':') + 2, tmp.end(), ch);

    if (occur >= min && occur <= max) {
      ++valid_pwords;
    }
  }

  output << valid_pwords << std::endl;
}
