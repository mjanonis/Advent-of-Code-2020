#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

int main()
{
  std::ifstream input{"day21.in"};
  std::ofstream output{"day21-2.out"};

  std::vector<std::string> ingredients;
  std::map<std::string, std::set<std::string>> allergen_to_ingredients;
  std::set<std::string> undiscovered_allergens;
  std::map<std::string, std::string> allergen_name;

  std::string tmp;
  while (getline(input, tmp)) {
    std::set<std::string> recipe;
    std::istringstream iss(tmp.substr(0, tmp.find('(') - 1));
    for (std::string ing; getline(iss, ing, ' ');) {
      recipe.insert(ing);
      ingredients.push_back(ing);
    }
    iss.clear();
    iss.str(tmp.substr(tmp.find("contains ") + 9));
    for (std::string all; getline(iss, all, ' ');) {
      all.pop_back();
      undiscovered_allergens.insert(all);
      if (allergen_to_ingredients.find(all) == allergen_to_ingredients.end()) {
        allergen_to_ingredients[all] = recipe;
      }
      else {
        std::set<std::string> intersection;
        std::set_intersection(
            allergen_to_ingredients[all].begin(),
            allergen_to_ingredients[all].end(), recipe.begin(), recipe.end(),
            std::inserter(intersection, intersection.begin()));
        allergen_to_ingredients[all] = intersection;
      }
    }
  }

  while (!undiscovered_allergens.empty()) {
    std::string to_delete;
    for (auto& ati : allergen_to_ingredients) {
      if (ati.second.size() == 1) {
        undiscovered_allergens.erase(ati.first);
        allergen_name[ati.first] = *ati.second.begin();
        to_delete = *ati.second.begin();
        break;
      }
    }
    for (auto& ati : allergen_to_ingredients) {
      ati.second.erase(to_delete);
    }
  }

  std::string dil = "";
  for (const auto& an : allergen_name) {
    dil += an.second + ",";
  }
  // Remove last comma
  dil.pop_back();

  output << dil << std::endl;
}
