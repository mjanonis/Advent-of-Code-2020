#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream input{"day05.in"};
  std::ofstream output{"day05-2.out"};

  std::string boarding_pass;
  std::vector<size_t> all_sids, plane_sids, missing_sids(1024);

  for (size_t i = 0; i < 128; ++i) {
    for (size_t j = 0; j < 8; ++j) {
      all_sids.push_back(i * 8 + j);
    }
  }

  while (getline(input, boarding_pass)) {
    int lr = 0, hr = 127, lc = 0, hc = 7, row = -1, col = -1, sid = -1;

    // Get the row
    for (size_t i = 0; i < 7; ++i) {
      char c = boarding_pass[i];
      if (c == 'F') {
        hr = (lr + hr) / 2;
      }
      if (c == 'B') {
        lr = std::ceil((lr + hr) / 2.0);
      }
    }

    assert(lr == hr);
    row = lr;

    for (size_t i = 7; i < boarding_pass.length(); ++i) {
      char c = boarding_pass[i];
      if (c == 'L') {
        hc = (lc + hc) / 2;
      }
      if (c == 'R') {
        lc = std::ceil((lc + hc) / 2.0);
      }
    }

    assert(lc == hc);
    col = lc;

    sid = row * 8 + col;
    plane_sids.push_back(sid);
  }
  std::sort(all_sids.begin(), all_sids.end());
  std::sort(plane_sids.begin(), plane_sids.end());
  auto it =
      std::set_difference(all_sids.begin(), all_sids.end(), plane_sids.begin(),
                          plane_sids.end(), missing_sids.begin());
  missing_sids.resize(it - missing_sids.begin());

  // Alternatively, just print out all missing_sids and select the odd one out
  for (size_t i = 0; i < missing_sids.size(); ++i) {
    if (missing_sids[i + 1] - missing_sids[i] == 1) {
      continue;
    }
    output << missing_sids[i + 1] << std::endl;
    break;
  }
}
