#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

bool out_of_range(const std::vector<std::string>& vec, int y, int x)
{
  if (y < 0 || y >= vec.size() || x < 0 || x >= vec[0].size()) {
    return true;
  }
  return false;
}

size_t vis_occupied_seats(const std::vector<std::string>& layout, int y, int x)
{
  size_t occ = 0;

  // N, NE, E, SE, S, SW, W, NW
  int yd[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
  int xd[8] = {0, 1, 1, 1, 0, -1, -1, -1};

  for (int i = 0; i < 8; ++i) {
    int yn = y + yd[i];
    int xn = x + xd[i];
    while (!out_of_range(layout, yn, xn) && layout[yn][xn] == '.') {
      yn += yd[i];
      xn += xd[i];
    }
    if (out_of_range(layout, yn, xn)) {
      continue;
    }
    if (layout[yn][xn] == '#') {
      ++occ;
    }
  }
  return occ;
}

int main()
{
  std::ifstream input{"day11.in"};
  std::ofstream output{"day11-2.out"};

  std::vector<std::string> layout;
  std::string tmp;
  size_t occ_seats = 0;

  while (getline(input, tmp)) {
    layout.push_back(tmp);
  }

  std::vector<std::string> old_layout(layout);

  do {
    old_layout = layout;
    for (int y = 0; y < layout.size(); ++y) {
      for (int x = 0; x < layout[y].size(); ++x) {
        size_t vis_occ = vis_occupied_seats(old_layout, y, x);
        if (old_layout[y][x] == 'L' && vis_occ == 0) {
          layout[y][x] = '#';
        }
        else if (old_layout[y][x] == '#' && vis_occ >= 5) {
          layout[y][x] = 'L';
        }
      }
    }
  } while (old_layout != layout);

  for (auto s : layout) {
    occ_seats += std::count(s.begin(), s.end(), '#');
  }

  output << occ_seats << std::endl;
}
