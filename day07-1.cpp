#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void get_containing_bags(
    const std::string& color, std::set<std::string>& contains_sgold_bag,
    const std::unordered_map<std::string, std::set<std::string>>& contained_in)
{
  // Check if key exists before trying to access
  if (contained_in.find(color) == contained_in.end()) {
    return;
  }
  for (auto c : contained_in.at(color)) {
    contains_sgold_bag.insert(c);
    get_containing_bags(c, contains_sgold_bag, contained_in);
  }
}

int main()
{
  std::ifstream input{"day07.in"};
  std::ofstream output{"day07-1.out"};

  std::string tmp;

  // Maps from a bag color to where it is contained
  std::unordered_map<std::string, std::set<std::string>> contained_in;
  while (getline(input, tmp)) {
    std::string color = tmp.substr(0, tmp.find("bags") - 1);

    // The rest of the input (following the word contain)
    std::string rest = tmp.substr(tmp.find("contain") + 7);
    if (rest == " no other bags.") {
      continue;
    }
    std::istringstream ss(rest);
    std::string count_color;
    // The strings from the stringstream will have a leading space
    while (getline(ss, count_color, ',')) {
      // Remove the leading space and leave just the count and the color
      count_color = count_color.substr(1, count_color.find(" bag") - 1);
      std::string inner_bag = count_color.substr(count_color.find(' ') + 1);
      contained_in[inner_bag].insert(color);
    }
  }
  std::set<std::string> contains_sgold_bag;
  get_containing_bags("shiny gold", contains_sgold_bag, contained_in);
  output << contains_sgold_bag.size() << std::endl;
}
