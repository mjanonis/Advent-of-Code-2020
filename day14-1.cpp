#include <algorithm>
#include <bitset>
#include <fstream>
#include <map>

int main()
{
  std::ifstream input{"day14.in"};
  std::ofstream output{"day14-1.out"};

  // BM0 - &, BM1 - |
  std::bitset<36> bm0(0xFFFFFFFFF), bm1(0);
  std::map<unsigned long long int, std::bitset<36>> memory;
  std::string tmp;

  while (getline(input, tmp)) {
    if (tmp[1] == 'a') {
      bm0 = 0xFFFFFFFFF;
      bm1.reset();

      tmp = tmp.substr(tmp.find_last_of(" ") + 1);
      std::reverse(tmp.begin(), tmp.end());
      for (size_t i = 0; i < tmp.size(); ++i) {
        if (tmp[i] == '0') {
          bm0.set(i, false);
          continue;
        }
        if (tmp[i] == '1') {
          bm1.set(i, true);
          continue;
        }
      }
      continue;
    }

    unsigned long long int addr =
        std::stoul(tmp.substr(tmp.find_first_of('[') + 1));
    std::bitset<36> val(std::stoul(tmp.substr(tmp.find_first_of('=') + 2)));
    val &= bm0;
    val |= bm1;
    memory[addr] = val;
  }

  unsigned long long int sum = 0;
  for (auto av : memory) {
    sum += av.second.to_ullong();
  }

  output << sum << std::endl;
}
