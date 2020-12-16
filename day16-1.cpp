#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

int main()
{
  std::ifstream input{"day16.in"};
  std::ofstream output{"day16-1.out"};

  // Maps a field name to the corresponding rule
  std::map<std::string, std::map<int, bool>> field_to_rules;
  std::vector<int> my_ticket;
  std::vector<std::vector<int>> nearby_tickets;
  std::string tmp;

  // Get the rules
  while (getline(input, tmp) && tmp.size()) {
    std::string field = tmp.substr(0, tmp.find(':'));
    std::istringstream rules(tmp.substr(tmp.find(':') + 2));
    while (getline(rules, tmp, ' ')) {
      if (tmp == "or") {
        continue;
      }
      int min = stoi(tmp.substr(0, tmp.find('-')));
      int max = stoi(tmp.substr(tmp.find('-') + 1));

      for (int i = min; i <= max; ++i) {
        field_to_rules[field][i] = true;
      }
    }
  }

  // Should read "your ticket:"
  getline(input, tmp);
  assert(tmp == "your ticket:");
  // Get the actual values
  getline(input, tmp);
  std::istringstream iss(tmp);
  while (getline(iss, tmp, ',')) {
    my_ticket.push_back(std::stoi(tmp));
  }
  // Skip empty line
  getline(input, tmp);
  // Should read "nearby tickets:"
  getline(input, tmp);
  assert(tmp == "nearby tickets:");
  while (getline(input, tmp)) {
    iss.clear();
    iss.str(tmp);
    std::vector<int> ticket;
    while (getline(iss, tmp, ',')) {
      ticket.push_back(stoi(tmp));
    }
    nearby_tickets.push_back(ticket);
  }

  int error_rate = 0;
  for (const auto& n : nearby_tickets) {
    for (const auto& t : n) {
      bool valid = false;
      for (const auto& f : field_to_rules) {
        if (f.second.find(t) != f.second.end()) {
          valid = true;
        }
      }
      if (!valid) {
        error_rate += t;
      }
    }
  }

  output << error_rate << std::endl;
}
