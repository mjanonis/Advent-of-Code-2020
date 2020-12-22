#include <cassert>
#include <deque>
#include <fstream>
#include <iterator>
#include <map>

// FIXME: Naive recursive solution, no optimizations whatsoever

// Returns p1, p2 decks
std::pair<std::deque<int>, std::deque<int>> play(std::deque<int>& p1,
                                                 std::deque<int>& p2)
{
  std::map<std::deque<int>, std::map<std::deque<int>, int>> order;
  while (!p1.empty() && !p2.empty()) {
    if (order.find(p1) != order.end() &&
        order[p1].find(p2) != order[p1].end()) {
      return {p1, std::deque<int>()};
    }
    order[p1][p2] = 1;
    int p1f = p1.front();
    int p2f = p2.front();
    p1.pop_front();
    p2.pop_front();

    if (p1f <= p1.size() && p2f <= p2.size()) {
      std::deque<int> p1sb, p2sb;
      std::copy(p1.begin(), p1.begin() + p1f, std::back_inserter(p1sb));
      std::copy(p2.begin(), p2.begin() + p2f, std::back_inserter(p2sb));

      std::pair<std::deque<int>, std::deque<int>> res = play(p1sb, p2sb);
      if (res.first.empty()) {
        p2.push_back(p2f);
        p2.push_back(p1f);
      }
      else {
        p1.push_back(p1f);
        p1.push_back(p2f);
      }
    }
    else {
      if (p1f > p2f) {
        p1.push_back(p1f);
        p1.push_back(p2f);
      }
      else {
        p2.push_back(p2f);
        p2.push_back(p1f);
      }
    }
  }
  return {p1, p2};
}

int main()
{
  std::ifstream input{"day22.in"};
  std::ofstream output{"day22-2.out"};

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

  std::pair<std::deque<int>, std::deque<int>> res = play(p1, p2);

  size_t winning_score = 0;
  size_t mult = 1;

  std::deque<int>& winner = res.first.empty() ? res.second : res.first;

  for (auto it = winner.rbegin(); it != winner.rend(); ++it) {
    winning_score += *it * mult;
    ++mult;
  }

  output << winning_score << std::endl;
}
