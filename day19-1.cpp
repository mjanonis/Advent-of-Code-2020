#include <algorithm>
#include <cctype>
#include <fstream>
#include <regex>
#include <sstream>
#include <vector>

int main()
{
  std::ifstream input{"day19.in"};
  std::ofstream output{"day19-1.out"};

  std::vector<std::string> rules;
  std::string tmp;

  while (getline(input, tmp) && tmp.length()) {
    rules.push_back(tmp);
  }

  std::sort(rules.begin(), rules.end(),
            [](const std::string& s1, const std::string& s2) {
              return stoi(s1.substr(0, s1.find(':'))) <
                     stoi(s2.substr(0, s2.find(':')));
            });

  for (auto& s : rules) {
    s = s.substr(s.find(':') + 2);
  }

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
