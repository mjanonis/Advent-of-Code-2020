#include <fstream>
#include <map>

unsigned int MDistance(const std::pair<int, int>& a,
                       const std::pair<int, int>& b)
{
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int main()
{
  std::ifstream input{"day12.in"};
  std::ofstream output{"day12-2.out"};

  std::string tmp;

  // x, y
  std::pair<int, int> ship{0, 0};
  std::pair<int, int> waypoint{10, 1};
  int xn = 0, yn = 0;

  std::map<int, int> cos;
  std::map<int, int> sin;

  // cos(-x) = cos(x)
  cos[0] = 1;
  cos[90] = 0;
  cos[180] = -1;
  cos[270] = 0;

  // sin(-x) = -sin(x)
  sin[0] = 0;
  sin[90] = 1;
  sin[180] = 0;
  sin[270] = -1;

  while (getline(input, tmp)) {
    char action = tmp[0];
    int mag = std::stoi(tmp.substr(1));
    switch (action) {
    case 'N':
      waypoint.second += mag;
      break;
    case 'S':
      waypoint.second -= mag;
      break;
    case 'E':
      waypoint.first += mag;
      break;
    case 'W':
      waypoint.first -= mag;
      break;
    case 'L':
      mag %= 360;
      xn = waypoint.first * cos[mag] - waypoint.second * sin[mag];
      yn = waypoint.second * cos[mag] + waypoint.first * sin[mag];
      waypoint.first = xn;
      waypoint.second = yn;
      break;
    case 'R':
      mag %= 360;
      xn = waypoint.first * cos[mag] - waypoint.second * -sin[mag];
      yn = waypoint.second * cos[mag] + waypoint.first * -sin[mag];
      waypoint.first = xn;
      waypoint.second = yn;
      break;
    case 'F':
      ship.first += mag * waypoint.first;
      ship.second += mag * waypoint.second;
      break;
    }
  }

  output << MDistance({ship.first, ship.second}, {0, 0}) << std::endl;
}
