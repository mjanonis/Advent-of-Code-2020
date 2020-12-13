#include <fstream>
#include <sstream>
#include <vector>

int main()
{
  std::ifstream input{"day13.in"};
  std::ofstream output{"day13-1.out"};

  unsigned int earliest_ts;
  std::string tmp;
  std::vector<unsigned int> busIDs;

  getline(input, tmp);
  earliest_ts = std::stoi(tmp);
  getline(input, tmp);
  std::istringstream iss(tmp);

  while (getline(iss, tmp, ',')) {
    if (tmp == "x") {
      continue;
    }
    busIDs.push_back(std::stoi(tmp));
  }

  bool dep = false;
  unsigned int ts = earliest_ts, busID;
  while (!dep) {
    ++ts;
    for (auto x : busIDs) {
      if (ts % x == 0) {
        busID = x;
        dep = true;
        break;
      }
    }
  }

  output << busID * (ts - earliest_ts) << std::endl;
}
