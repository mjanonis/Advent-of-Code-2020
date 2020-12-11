#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main()
{
  std::ifstream input{"day01.in"};
  std::ofstream output{"day01-1.out"};

  std::vector<int> numbers;
  std::unordered_map<int, int> hmap;
  int tmp;

  while (input >> tmp) {
    numbers.push_back(tmp);
  }

  for (size_t i = 0; i < numbers.size(); ++i) {
    if (hmap.find(2020 - numbers[i]) != hmap.end()) {
      output << numbers[hmap[2020 - numbers[i]]] * numbers[i] << '\n';
    }
    hmap[numbers[i]] = i;
  }
}
