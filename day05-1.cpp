#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream input{"day05.in"};
  std::ofstream output{"day05-1.out"};

  std::string boarding_pass;
  int max_sid = -1;
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
    if (sid > max_sid) {
      max_sid = sid;
    }
  }
  output << max_sid << std::endl;
}
