#include <fstream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

// NOTE - this isn't an optimal solution, so it takes a minute to run. Will
// optimize in a couple of hours.

int main()
{
  std::ifstream input{"day15.in"};
  std::ofstream output{"day15-2.out"};

  // Maps a number to its age
  std::map<int, std::queue<int>> numbers;

  std::string tmp;
  getline(input, tmp);
  std::istringstream iss(tmp);

  int turn = 1;
  int last_number = 0;
  while (getline(iss, tmp, ',')) {
    numbers[stoi(tmp)].push(turn);
    last_number = stoi(tmp);
    ++turn;
  }

  for (; turn <= 30000000; ++turn) {
    if (numbers[last_number].size() == 1) {
      last_number = 0;
    }
    else {
      last_number = numbers[last_number].back() - numbers[last_number].front();
    }

    if (numbers[last_number].size() == 1 || numbers[last_number].size() == 0) {
      numbers[last_number].push(turn);
    }
    else {
      numbers[last_number].pop();
      numbers[last_number].push(turn);
    }
  }
  output << last_number << std::endl;
}
