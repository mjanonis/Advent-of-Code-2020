#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>

int main()
{
  std::ifstream input{"day09.in"};
  std::ofstream output{"day09-2.out"};

  std::vector<long int> data;
  long int tmp = 0;
  // Get the preamble
  for (int i = 0; i < 25; ++i) {
    input >> tmp;
    data.push_back(tmp);
  }

  std::unordered_map<long int, long int> hmap;
  unsigned long int start = 0;
  long int inv_number = 0;
  while (input >> tmp) {
    bool pair_found = false;
    hmap.clear();
    for (unsigned long int i = start; i < data.size(); ++i) {
      if (hmap.find(tmp - data[i]) != hmap.end()) {
        pair_found = true;
        break;
      }
      hmap[data[i]] = i;
    }
    if (!pair_found) {
      inv_number = tmp;
      break;
    }
    data.push_back(tmp);
    ++start;
  }

  int curr_sum = data[0];
  start = 0;
  unsigned long int end = 0;

  for (size_t i = 1; i < data.size(); ++i) {
    while (curr_sum > inv_number && start < i - 1) {
      curr_sum = curr_sum - data[start];
      ++start;
    }

    if (curr_sum == inv_number) {
      end = i - 1;
      break;
    }
    if (i < data.size()) {
      curr_sum += data[i];
    }
  }

  std::vector<long int> cset(data.begin() + start, data.begin() + end + 1);
  std::sort(cset.begin(), cset.end());
  output << cset[0] + cset[cset.size() - 1] << std::endl;
}
