#include <algorithm>
#include <cassert>
#include <fstream>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <unordered_set>
#include <vector>

struct Tile {
  Tile() = default;
  Tile(std::vector<std::string> d) : data{d} {}
  std::vector<std::string> data;
  std::vector<std::string> edges;
};

std::string reverse_str(std::string s)
{
  std::reverse(s.begin(), s.end());
  return s;
}

// Updates the edges for a tile
// Edges are ordered TOP, RIGHT, BOTTOM, LEFT
void update_edges(Tile& t)
{
  t.edges.clear();
  t.edges.push_back(t.data[0]);

  std::string l, r;
  for (const auto& row : t.data) {
    l.push_back(row[0]);
    r.push_back(row[row.length() - 1]);
  }

  t.edges.push_back(r);
  t.edges.push_back(t.data[t.data.size() - 1]);
  t.edges.push_back(l);
}

void rot_left(std::vector<std::string>& m)
{
  size_t n = m.size();
  for (size_t i = 0; i < n / 2; ++i) {
    for (size_t j = i; j < n - i - 1; ++j) {
      char tmp = m[i][j];
      m[i][j] = m[j][n - 1 - i];
      m[j][n - 1 - i] = m[n - 1 - i][n - 1 - j];
      m[n - 1 - i][n - 1 - j] = m[n - 1 - j][i];
      m[n - 1 - j][i] = tmp;
    }
  }
}

void flip_y(std::vector<std::string>& m) { std::reverse(m.begin(), m.end()); }

void generate_tile_variations(const size_t& t_id, const Tile& t,
                              std::map<size_t, std::vector<Tile>>& tv)
{
  // 8 possible variations per tile
  // 4 rotations per flip

  Tile cpy = t;
  for (size_t i = 0; i < 4; ++i) {
    rot_left(cpy.data);
    update_edges(cpy);
    tv[t_id].push_back(cpy);
  }
  flip_y(cpy.data);
  update_edges(cpy);
  for (size_t i = 0; i < 4; ++i) {
    rot_left(cpy.data);
    update_edges(cpy);
    tv[t_id].push_back(cpy);
  }
}

void build_image(std::map<int, std::map<int, Tile>>& image,
                 const std::map<size_t, Tile>& tiles,
                 const std::map<size_t, std::vector<Tile>>& tile_variations)
{
  int yd[4] = {-1, 0, 1, 0};
  int xd[4] = {0, 1, 0, -1};

  std::unordered_set<size_t> remaining_tiles;
  std::queue<std::pair<int, int>> Q;

  for (const auto& t : tiles) {
    remaining_tiles.insert(t.first);
  }
  remaining_tiles.erase(tiles.begin()->first);
  image[0][0] = tiles.begin()->second;
  Q.push({0, 0});

  while (!Q.empty()) {
    std::pair<int, int> node = Q.front();
    Q.pop();

    for (size_t i = 0; i < 4; ++i) {
      bool found = false;
      if (image.find(node.first + yd[i]) == image.end() ||
          image.at(node.first + yd[i]).find(node.second + xd[i]) ==
              image.at(node.first + yd[i]).end()) {
        for (const auto& id : remaining_tiles) {
          if (found) {
            break;
          }
          for (const auto& tv : tile_variations.at(id)) {
            if (found) {
              break;
            }
            if (image[node.first][node.second].edges[i] ==
                tv.edges[(i + 2) % 4]) {
              image[node.first + yd[i]][node.second + xd[i]] = tv;
              remaining_tiles.erase(id);
              Q.push({node.first + yd[i], node.second + xd[i]});
              found = true;
            }
          }
        }
      }
    }
  }
  assert(remaining_tiles.empty());
}

int main()
{
  std::ifstream input{"day20.in"};
  std::ofstream output{"day20-2.out"};

  std::string tmp;
  std::vector<std::string> r;
  size_t t_id;

  std::map<size_t, Tile> tiles;
  std::map<size_t, std::vector<Tile>> tile_variations;

  while (getline(input, tmp)) {
    if (tmp.length() == 0) {
      tiles[t_id] = Tile(r);
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
  // Deal with the last til
  tiles[t_id] = Tile(r);

  // Populate the edges of each tile
  // TOP, RIGHT, BOTTOM, LEFT
  for (auto& t : tiles) {
    update_edges(t.second);
  }

  for (const auto& t : tiles) {
    generate_tile_variations(t.first, t.second, tile_variations);
  }

  // y, x, tile
  std::map<int, std::map<int, Tile>> image;
  std::vector<std::string> flat_image;

  build_image(image, tiles, tile_variations);

  size_t fi = 0;
  for (auto& y : image) {
    for (size_t i = 1; i < y.second.begin()->second.data.size() - 1; ++i) {
      flat_image.push_back("");
    }
    for (auto& x : y.second) {
      for (size_t i = 1; i < x.second.data.size() - 1; ++i) {
        flat_image[fi + i - 1] +=
            x.second.data[i].substr(1, x.second.data[i].length() - 2);
      }
    }
    fi += y.second.begin()->second.data.size() - 2;
  }

  std::vector<std::regex> monster = {
      std::regex("..................#.", std::regex::optimize),
      std::regex("#....##....##....###", std::regex::optimize),
      std::regex(".#..#..#..#..#..#...", std::regex::optimize)};

  std::vector<std::vector<size_t>> offsets{
      {18}, {0, 5, 6, 11, 12, 17, 18, 19}, {1, 4, 7, 10, 13, 16}};

  for (size_t v = 0; v < 8; ++v) {
    if (v == 4) {
      flip_y(flat_image);
    }
    rot_left(flat_image);
    for (size_t i = 0; i < flat_image.size() - 2; ++i) {
      std::smatch m1, m2, m3;
      if (std::regex_search(flat_image[i], m1, monster[0])) {
        if (std::regex_search(flat_image[i + 1], m2, monster[1])) {
          if (std::regex_search(flat_image[i + 2], m3, monster[2])) {
            std::vector<std::smatch> matches{m1, m2, m3};
            for (size_t o = 0; o < 3; ++o) {
              for (size_t l = 0; l < offsets[o].size(); ++l) {
                flat_image[i + o]
                          [matches[o].prefix().length() + offsets[o][l]] = 'O';
              }
            }
          }
        }
      }
    }
  }

  size_t roughness = 0;
  for (const auto& s : flat_image) {
    roughness += std::count(s.begin(), s.end(), '#');
  }
  output << roughness << std::endl;
}
