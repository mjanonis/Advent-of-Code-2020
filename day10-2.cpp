#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

int main()
{
  std::ifstream input{"day10.in"};
  std::ofstream output{"day10-2.out"};

  std::vector<unsigned int> adapters;
  unsigned int tmp;
  while (input >> tmp) {
    adapters.push_back(tmp);
  }

  unsigned int device_joltage =
      *std::max_element(adapters.begin(), adapters.end()) + 3;

  std::sort(adapters.begin(), adapters.end());
  adapters.push_back(device_joltage);

  std::map<int, unsigned long int> arrangements;
  arrangements[0] = 1;

  for (int i = 0; i < adapters.size(); ++i) {
    arrangements[adapters[i]] = arrangements[adapters[i] - 1] +
                                arrangements[adapters[i] - 2] +
                                arrangements[adapters[i] - 3];
  }

  output << arrangements.rbegin()->second << std::endl;
}
