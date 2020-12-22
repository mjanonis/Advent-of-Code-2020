#include <cassert>
#include <deque>
#include <fstream>

int main()
{
  std::ifstream input{"day22.in"};
  std::ofstream output{"day22-1.out"};

  std::deque<int> p1;
  std::deque<int> p2;

  std::string tmp;
  getline(input, tmp);
  assert(tmp == "Player 1:");
  while (getline(input, tmp) && !tmp.empty()) {
    p1.push_back(stoi(tmp));
  }
  getline(input, tmp);
  assert(tmp == "Player 2:");
  while (getline(input, tmp)) {
    p2.push_back(stoi(tmp));
  }

  while (!p1.empty() && !p2.empty()) {
    if (p1.front() > p2.front()) {
      p1.push_back(p1.front());
      p1.push_back(p2.front());
    }
    else {
      p2.push_back(p2.front());
      p2.push_back(p1.front());
    }
    p1.pop_front();
    p2.pop_front();
  }

  size_t winning_score = 0;
  size_t mult = 1;

  std::deque<int>& winner = p1.empty() ? p2 : p1;
  for (auto it = winner.rbegin(); it != winner.rend(); ++it) {
    winning_score += *it * mult;
    ++mult;
  }

  output << winning_score << std::endl;
}
