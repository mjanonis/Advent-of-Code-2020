#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>

int main()
{
  std::ifstream input{"day10.in"};
  std::ofstream output{"day10-1.out"};

  std::vector<unsigned int> adapters;
  unsigned int tmp;
  while (input >> tmp) {
    adapters.push_back(tmp);
  }

  unsigned int curr_jotalge = 0;
  std::unordered_map<unsigned int, unsigned int> diff_count;
  std::sort(adapters.begin(), adapters.end());

  for (auto x : adapters) {
    ++diff_count[x - curr_jotalge];
    curr_jotalge = x;
  }

  ++diff_count[3];
  output << diff_count[1] * diff_count[3] << std::endl;
}
