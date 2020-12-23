#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

void update_indices(const std::vector<int>& cups, std::map<int, size_t>& index)
{
  for (size_t i = 0; i < cups.size(); ++i) {
    index[cups[i]] = i;
  }
}

// Modulo operator that always returns a positive remainder
size_t mod(const int& lhs, const int& rhs) { return (rhs + (lhs % rhs)) % rhs; }

int main()
{
  std::ifstream input{"day23.in"};
  std::ofstream output{"day23-1.out"};

  std::map<int, size_t> index;
  std::vector<int> cups;

  std::string tmp;
  getline(input, tmp);
  std::istringstream iss(tmp);
  for (char c; iss >> c;) {
    cups.push_back(c - '0');
  }

  for (size_t i = 0; i < cups.size(); ++i) {
    index[cups[i]] = i;
  }

  size_t curr_cup_index = 0;
  size_t cups_size = cups.size();

  for (size_t i = 0; i < 100; ++i) {
    for (const auto& x : cups) {
      if (x == cups[curr_cup_index]) {
        continue;
      }
    }

    size_t ci1, ci2, ci3;
    ci1 = (curr_cup_index + 1) % cups_size;
    ci2 = (curr_cup_index + 2) % cups_size;
    ci3 = (curr_cup_index + 3) % cups_size;

    int cdl = cups[curr_cup_index] - 1;
    int curr_cup = cups[curr_cup_index];

    while (cdl == cups[ci1] || cdl == cups[ci2] || cdl == cups[ci3] ||
           cdl < index.begin()->first) {
      cdl -= 1;
      if (cdl < index.begin()->first) {
        cdl = index.rbegin()->first;
      }
    }

    while (index[cdl] > ci1) {
      std::iter_swap(cups.begin() + ci3, cups.begin() + (ci3 + 1) % cups_size);
      std::iter_swap(cups.begin() + ci2, cups.begin() + (ci2 + 1) % cups_size);
      std::iter_swap(cups.begin() + ci1, cups.begin() + (ci1 + 1) % cups_size);
      ci1 = (ci1 + 1) % cups_size;
      ci2 = (ci2 + 1) % cups_size;
      ci3 = (ci3 + 1) % cups_size;

      update_indices(cups, index);
    }
    while (index[cdl] < ci1 && ci1 - index[cdl] != 1) {
      std::iter_swap(cups.begin() + ci1,
                     cups.begin() + mod(ci1 - 1, cups_size));
      std::iter_swap(cups.begin() + ci2,
                     cups.begin() + mod(ci2 - 1, cups_size));
      std::iter_swap(cups.begin() + ci3,
                     cups.begin() + mod(ci3 - 1, cups_size));
      ci1 = mod((ci1 - 1), cups_size);
      ci2 = mod((ci2 - 1), cups_size);
      ci3 = mod((ci3 - 1), cups_size);

      update_indices(cups, index);
    }

    curr_cup_index = (index[curr_cup] + 1) % cups_size;
  }

  std::rotate(cups.begin(), std::find(cups.begin(), cups.end(), 1), cups.end());

  for (auto it = cups.begin() + 1; it != cups.end(); ++it) {
    output << *it;
  }

  output << std::endl;
}
