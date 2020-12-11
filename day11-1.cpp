#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

size_t adj_occupied_seats(const std::vector<std::string>& layout, int y, int x)
{
  size_t occ = 0;

  // N, NE, E, SE, S, SW, W, NW
  int yd[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
  int xd[8] = {0, 1, 1, 1, 0, -1, -1, -1};

  for (int i = 0; i < 8; ++i) {
    int yn = y + yd[i];
    int xn = x + xd[i];
    // Check for out of range values
    if (yn < 0 || yn >= static_cast<int>(layout.size()) || xn < 0 ||
        xn >= static_cast<int>(layout[0].size())) {
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
  std::ofstream output{"day11-1.out"};

  std::vector<std::string> layout;
  std::string tmp;
  size_t occ_seats = 0;

  while (getline(input, tmp)) {
    layout.push_back(tmp);
  }

  std::vector<std::string> old_layout(layout);

  do {
    old_layout = layout;
    for (size_t y = 0; y < layout.size(); ++y) {
      for (size_t x = 0; x < layout[y].size(); ++x) {
        if (old_layout[y][x] == '.') {
          continue;
        }
        size_t adj_occ = adj_occupied_seats(old_layout, y, x);
        if (old_layout[y][x] == 'L' && adj_occ == 0) {
          layout[y][x] = '#';
        }
        else if (old_layout[y][x] == '#' && adj_occ >= 4) {
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
