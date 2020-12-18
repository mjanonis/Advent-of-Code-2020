#include <fstream>
#include <map>

void update_active_neighbour_count(
    std::map<int, std::map<int, std::map<int, std::pair<bool, unsigned int>>>>&
        cubes,
    int x, int y, int z, bool new_state)
{
  // C, N, NE, E, SE, S, SW, W, NW
  int xd[9] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
  int yd[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
  int zd[3] = {-1, 0, 1};

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (xd[i] == 0 && yd[i] == 0 && zd[j] == 0) {
        continue;
      }
      cubes[x + xd[i]][y + yd[i]][z + zd[j]].second +=
          (static_cast<int>(new_state) -
           static_cast<int>(cubes[x][y][z].first));
    }
  }
}

int main()
{
  std::ifstream input{"day17.in"};
  std::ofstream output{"day17-1.out"};

  // x, y, z, active + active_neighbours
  std::map<int, std::map<int, std::map<int, std::pair<bool, unsigned int>>>>
      cubes;

  std::string tmp;
  for (int y = 0; getline(input, tmp); ++y) {
    for (size_t i = 0; i < tmp.length(); ++i) {
      int x = i;
      cubes[x][y][0].first = false;
      update_active_neighbour_count(cubes, x, y, 0, tmp[i] == '#');
      cubes[x][y][0].first = tmp[i] == '#';
    }
  }

  std::map<int, std::map<int, std::map<int, std::pair<bool, unsigned int>>>>
      old_cubes;

  for (int i = 0; i < 6; ++i) {
    old_cubes = cubes;
    for (const auto& x : old_cubes) {
      for (const auto& y : x.second) {
        for (const auto& z : y.second) {

          if (z.second.first &&
              (z.second.second == 2 || z.second.second == 3)) {
            continue;
          }
          else if (z.second.first) {
            update_active_neighbour_count(cubes, x.first, y.first, z.first,
                                          false);
            cubes[x.first][y.first][z.first].first = false;
            continue;
          }

          if (!z.second.first && z.second.second == 3) {
            update_active_neighbour_count(cubes, x.first, y.first, z.first,
                                          true);
            cubes[x.first][y.first][z.first].first = true;
            continue;
          }
          else if (!z.second.first) {
            continue;
          }
        }
      }
    }
  }

  size_t active_count = 0;
  for (const auto& x : cubes) {
    for (const auto& y : x.second) {
      for (const auto& z : y.second) {
        active_count += z.second.first;
      }
    }
  }

  output << active_count << std::endl;
}
