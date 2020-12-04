#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main()
{
  std::ifstream input{"day1.in"};
  std::ofstream output{"day1-2.out"};

  std::vector<int> numbers;
  int tmp;

  while (input >> tmp) {
    numbers.push_back(tmp);
  }

  for (size_t i = 0; i < numbers.size() - 2; ++i) {
    std::unordered_map<int, int> hmap;
    int sum = 2020 - numbers[i];
    for (size_t j = i + 1; j < numbers.size(); ++j) {
      if (hmap.find(sum - numbers[j]) != hmap.end()) {
        output << numbers[i] * numbers[j] * (sum - numbers[j]) << '\n';
      }
      hmap[numbers[j]] = j;
    }
  }
}
