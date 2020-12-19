#include <algorithm>
#include <cctype>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>

// FIXME: Disgusting solution, needs refactoring

#define _GLIBCXX_REGEX_STATE_LIMIT 2147483647

int main()
{
  std::ifstream input{"day19.in"};
  std::ofstream output{"day19-2.out"};

  std::map<int, std::string> rules;
  std::string tmp;

  while (getline(input, tmp) && tmp.length()) {
    rules[stoi(tmp.substr(0, tmp.find(':')))] = tmp.substr(tmp.find(':') + 2);
  }

  rules[8] = "( 42 )+"; // Equivalent to 42 | 42 8
  rules[11] = "( 42 31 ) | ( 42 42 31 31 ) | ( 42 42 42 31 31 31 ) | ( 42 42 "
              "42 42 31 31 31 31 ) | ( 42 42 42 42 42 31 31 31 31 31 ) | ( 42 "
              "42 42 42 42 42 31 31 31 31 31 31 )";

  rules[0].reserve(10000);
  std::istringstream iss(rules[0]);
  while (getline(iss, tmp, ' ')) {
    if (std::any_of(tmp.begin(), tmp.end(), ::isdigit)) {
      rules[0].replace(rules[0].find(tmp), tmp.length(),
                       "( " + rules[stoi(tmp)] + " )");
      iss.str(rules[0]);
      iss.clear();
    }
  }
  rules[0].erase(std::remove_if(rules[0].begin(), rules[0].end(), ::isspace),
                 rules[0].end());
  rules[0].erase(std::remove_if(rules[0].begin(), rules[0].end(),
                                [](const char& c) { return c == '"'; }),
                 rules[0].end());

  std::regex re(rules[0], std::regex::optimize);
  std::cmatch m;
  size_t valid_msgs = 0;

  while (getline(input, tmp)) {
    valid_msgs += std::regex_match(tmp.c_str(), m, re);
  }

  output << valid_msgs << std::endl;
}
