#include <algorithm>
#include <bitset>
#include <fstream>
#include <map>

void set_memory(std::map<unsigned long long int, unsigned long long int>& mem,
                std::string addr, unsigned long long int val)
{
  if (std::count(addr.begin(), addr.end(), 'X') == 0) {
    std::bitset<36> addr_bs(addr);
    mem[addr_bs.to_ullong()] = val;
    return;
  }
  std::string addr0 = addr, addr1 = addr;
  addr0.replace(addr0.find_first_of('X'), 1, "0");
  set_memory(mem, addr0, val);
  addr1.replace(addr1.find_first_of('X'), 1, "1");
  set_memory(mem, addr1, val);
}

int main()
{
  std::ifstream input{"day14.in"};
  std::ofstream output{"day14-2.out"};

  std::map<unsigned long long int, unsigned long long int> memory;
  std::string tmp, bm;

  while (getline(input, tmp)) {
    if (tmp[1] == 'a') {
      bm = tmp.substr(tmp.find_last_of(" ") + 1);
      continue;
    }
    std::bitset<36> addr_bs(std::stoul(tmp.substr(tmp.find_first_of('[') + 1)));
    std::string addr = addr_bs.to_string();
    unsigned long long int val =
        std::stoul(tmp.substr(tmp.find_first_of('=') + 2));

    // Apply the mask
    for (size_t i = 0; i < 36; ++i) {
      if (bm[i] == '0') {
        continue;
      }
      addr[i] = bm[i];
    }

    set_memory(memory, addr, val);
  }

  unsigned long long int sum = 0;
  for (auto x : memory) {
    sum += x.second;
  }

  output << sum << std::endl;
}
