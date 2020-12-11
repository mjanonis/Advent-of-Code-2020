#include <fstream>
#include <list>
#include <unordered_map>

int main()
{
  std::ifstream input{"day09.in"};
  std::ofstream output{"day09-1.out"};

  std::list<long int> data;
  long int tmp = 0;
  // Get the preamble
  for (int i = 0; i < 25; ++i) {
    input >> tmp;
    data.push_back(tmp);
  }

  std::unordered_map<long int, long int> hmap;

  while (input >> tmp) {
    bool pair_found = false;
    hmap.clear();
    for (auto x : data) {
      if (hmap.find(tmp - x) != hmap.end()) {
        pair_found = true;
        break;
      }
      hmap[x] = 1;
    }
    if (!pair_found) {
      output << tmp << std::endl;
      break;
    }
    data.pop_front();
    data.push_back(tmp);
  }
}
