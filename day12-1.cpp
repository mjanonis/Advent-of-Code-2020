#include <fstream>

struct Ship {
  int x = 0;
  int y = 0;

  // N, E, S, W
  int dir = 1;
};

unsigned int MDistance(const std::pair<int, int>& a,
                       const std::pair<int, int>& b)
{
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int main()
{
  std::ifstream input{"day12.in"};
  std::ofstream output{"day12-1.out"};

  int yd[4] = {-1, 0, 1, 0};
  int xd[4] = {0, 1, 0, -1};

  std::string tmp;
  Ship ship;

  while (getline(input, tmp)) {
    char action = tmp[0];
    int mag = std::stoi(tmp.substr(1));

    switch (action) {
    case 'N':
      ship.y -= mag;
      break;
    case 'S':
      ship.y += mag;
      break;
    case 'E':
      ship.x += mag;
      break;
    case 'W':
      ship.x -= mag;
      break;
    case 'L':
      mag /= 90;
      mag %= 4;
      ship.dir = (4 + ((ship.dir - mag) % 4)) % 4;
      break;
    case 'R':
      mag /= 90;
      mag %= 4;
      ship.dir = (4 + ((ship.dir + mag) % 4)) % 4;
      break;
    case 'F':
      ship.x += mag * xd[ship.dir];
      ship.y += mag * yd[ship.dir];
      break;
    }
  }
  output << MDistance({ship.x, ship.y}, {0, 0}) << std::endl;
}
