#include <fstream>
#include <set>
#include <string>
#include <vector>

int main()
{
  std::ifstream input{"day8.in"};
  std::ofstream output{"day8-1.out"};

  std::vector<std::pair<std::string, int>> program;
  std::string tmp;

  while (getline(input, tmp)) {
    std::string op = tmp.substr(0, tmp.find(' '));
    int arg = std::stoi(tmp.substr(tmp.find(' ') + 1));
    program.push_back(std::make_pair(op, arg));
  }

  std::set<int> visited_instr;
  int ip = 0, acc = 0;
  while (ip < program.size()) {
    if (visited_instr.find(ip) != visited_instr.end()) {
      break;
    }
    visited_instr.insert(ip);
    if (program[ip].first == "nop") {}
    else if (program[ip].first == "acc") {
      acc += program[ip].second;
    }
    else if (program[ip].first == "jmp") {
      ip += program[ip].second;
      continue;
    }
    ++ip;
  }
  output << acc << std::endl;
}
