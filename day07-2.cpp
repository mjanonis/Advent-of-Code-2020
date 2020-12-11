#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

size_t total_bag_contents(
    const std::string& color,
    const std::unordered_map<
        std::string, std::vector<std::pair<size_t, std::string>>>& contains)
{
  // Check if key exists before trying to access
  if (contains.find(color) == contains.end()) {
    return 0;
  }
  size_t sum = 0;
  for (auto cc : contains.at(color)) {
    sum += cc.first;
    sum += cc.first * total_bag_contents(cc.second, contains);
  }
  return sum;
}

int main()
{
  std::ifstream input{"day07.in"};
  std::ofstream output{"day07-2.out"};

  std::string tmp;

  // Maps from a bag color to its contents
  std::unordered_map<std::string, std::vector<std::pair<size_t, std::string>>>
      contains;
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
      size_t count = std::stoi(count_color.substr(0, count_color.find(' ')));
      std::string inner_bag = count_color.substr(count_color.find(' ') + 1);
      contains[color].push_back(std::make_pair(count, inner_bag));
    }
  }
  output << total_bag_contents("shiny gold", contains) << std::endl;
}
