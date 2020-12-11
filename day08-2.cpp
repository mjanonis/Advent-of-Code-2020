#include <fstream>
#include <set>
#include <string>
#include <vector>

int main()
{
  std::ifstream input{"day08.in"};
  std::ofstream output{"day08-2.out"};

  std::vector<std::pair<std::string, int>> program;
  std::string tmp;

  while (getline(input, tmp)) {
    std::string op = tmp.substr(0, tmp.find(' '));
    int arg = std::stoi(tmp.substr(tmp.find(' ') + 1));
    program.push_back(std::make_pair(op, arg));
  }

  std::set<int> visited_instr;
  int ip = 0, acc = 0;

  std::vector<std::pair<std::string, int>> program_orig{program};

  for (int i = 0; i < program_orig.size(); ++i) {
    if (program_orig[i].first == "acc") {
      continue;
    }
    ip = 0;
    acc = 0;
    visited_instr.clear();
    if (program[i].first == "jmp") {
      program[i].first = "nop";
    }
    else {
      program[i].first = "jmp";
    }

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

    if (ip == program.size()) {
      break;
    }
    program = program_orig;
  }

  output << acc << std::endl;
}
