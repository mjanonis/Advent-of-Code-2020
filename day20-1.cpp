#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

std::string reverse_str(std::string s)
{
  std::reverse(s.begin(), s.end());
  return s;
}

int main()
{
  std::ifstream input{"day20.in"};
  std::ofstream output{"day20-1.out"};

  std::string tmp;
  std::vector<std::string> r;
  size_t t_id;

  std::map<size_t, std::vector<std::string>> tiles;
  std::map<size_t, std::vector<std::string>> tile_edges;
  while (getline(input, tmp)) {
    if (tmp.length() == 0) {
      tiles[t_id] = r;
      t_id = 0;
      r.clear();
      continue;
    }
    if (tmp.find("Tile") != tmp.npos) {
      t_id = stoi(tmp.substr(tmp.find(' ') + 1));
      continue;
    }
    r.push_back(tmp);
  }
  // Deal with the last tile
  tiles[t_id] = r;

  std::map<std::string, size_t> edge_count;

  for (const auto& t : tiles) {
    ++edge_count[t.second[0]];
    ++edge_count[t.second[t.second.size() - 1]];
    ++edge_count[reverse_str(t.second[0])];
    ++edge_count[reverse_str(t.second[t.second.size() - 1])];

    std::string e1, e2;
    for (const auto& r : t.second) {
      e1.push_back(r[0]);
      e2.push_back(r[r.length() - 1]);
    }
    ++edge_count[e1];
    ++edge_count[e2];
    ++edge_count[reverse_str(e1)];
    ++edge_count[reverse_str(e2)];

    tile_edges[t.first].push_back(t.second[0]);
    tile_edges[t.first].push_back(t.second[t.second.size() - 1]);
    tile_edges[t.first].push_back(e1);
    tile_edges[t.first].push_back(e2);
  }

  unsigned long long int mult = 1;
  size_t n_corners = 0;

  for (const auto& t : tiles) {
    size_t n_unique = 0;

    for (const auto& edge : tile_edges[t.first]) {
      if (edge_count[edge] == 1) {
        ++n_unique;
      }
    }
    if (n_unique == 2) {
      ++n_corners;
      mult *= t.first;
    }
  }

  output << mult << std::endl;
}
