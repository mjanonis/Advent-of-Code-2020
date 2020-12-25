#include <fstream>
#include <map>
#include <sstream>

void update_black_neighbour_count(
    std::map<int, std::map<int, std::pair<bool, size_t>>>& tile, int q, int r,
    bool new_state)
{
  // W, NW, NE, E, SE, SW
  int qd[6] = {-1, 0, 1, 1, 0, -1};
  int rd[6] = {0, -1, -1, 0, 1, 1};

  for (size_t i = 0; i < 6; ++i) {
    tile[q + qd[i]][r + rd[i]].second +=
        (static_cast<int>(new_state) - static_cast<int>(tile[q][r].first));
  }
}

int main()
{
  std::ifstream input{"day24.in"};
  std::ofstream output{"day24-2.out"};

  // q, r, black + black_neighbours
  std::map<int, std::map<int, std::pair<bool, size_t>>> tile;

  // W, NW, NE, E, SE, SW
  std::map<std::string, int> qd = {{"w", -1}, {"nw", 0}, {"ne", 1},
                                   {"e", 1},  {"se", 0}, {"sw", -1}};
  std::map<std::string, int> rd = {{"w", 0}, {"nw", -1}, {"ne", -1},
                                   {"e", 0}, {"se", 1},  {"sw", 1}};

  std::string tmp;
  while (getline(input, tmp)) {
    int q = 0, r = 0;
    std::istringstream iss(tmp);
    tmp.clear();
    for (char c; iss >> c;) {
      tmp.push_back(c);
      if (c == 's' || c == 'n') {
        continue;
      }
      q += qd[tmp];
      r += rd[tmp];
      tmp.clear();
    }
    update_black_neighbour_count(tile, q, r, !tile[q][r].first);
    tile[q][r].first = !tile[q][r].first;
  }

  std::map<int, std::map<int, std::pair<bool, size_t>>> old_tile;
  for (int i = 0; i < 100; ++i) {
    old_tile = tile;
    for (const auto& q : old_tile) {
      for (const auto& r : q.second) {
        if (r.second.first && (r.second.second == 0 || r.second.second > 2)) {
          update_black_neighbour_count(tile, q.first, r.first, false);
          tile[q.first][r.first].first = false;
          continue;
        }
        else if (!r.second.first && r.second.second == 2) {
          update_black_neighbour_count(tile, q.first, r.first, true);
          tile[q.first][r.first].first = true;
          continue;
        }
      }
    }
  }
  size_t black_tiles = 0;
  for (const auto& q : tile) {
    for (const auto& r : q.second) {
      black_tiles += r.second.first;
    }
  }

  output << black_tiles << std::endl;
}
