#include <algorithm>
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
  std::vector<long int> my_ticket;
  std::vector<std::vector<long int>> nearby_tickets;
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
    std::vector<long int> ticket;
    while (getline(iss, tmp, ',')) {
      ticket.push_back(stoi(tmp));
    }
    nearby_tickets.push_back(ticket);
  }

  for (auto& n : nearby_tickets) {
    for (const auto& t : n) {
      bool valid = false;
      for (const auto& f : field_to_rules) {
        if (f.second.find(t) != f.second.end()) {
          valid = true;
        }
      }
      if (!valid) {
        n.clear();
      }
    }
  }

  // Delete invalid tickets
  for (auto it = nearby_tickets.begin(); it != nearby_tickets.end();) {
    if (it->empty()) {
      it = nearby_tickets.erase(it);
      continue;
    }
    ++it;
  }

  nearby_tickets.push_back(my_ticket);

  std::map<std::string, int> field_order;
  std::vector<std::string> candidates, curr_candidates;

  for (const auto& f : field_to_rules) {
    candidates.push_back(f.first);
  }

  for (size_t i = 0; i < field_to_rules.size(); ++i) {
    curr_candidates = candidates;

    for (const auto& t : nearby_tickets) {
      for (auto it = curr_candidates.begin(); it != curr_candidates.end();) {
        if (field_to_rules[*it].find(t[i]) == field_to_rules[*it].end()) {
          it = curr_candidates.erase(it);
          continue;
        }
        ++it;
      }
    }

    if (curr_candidates.size() == 1) {
      field_order[curr_candidates[0]] = i;
      candidates.erase(
          std::find(candidates.begin(), candidates.end(), curr_candidates[0]));
      i = 0;
      continue;
    }
  }

  long int mult = 1;

  for (const auto& fo : field_order) {
    if (fo.first.find("departure") != std::string::npos) {
      mult *= my_ticket[fo.second];
    }
  }

  output << mult << std::endl;
}
