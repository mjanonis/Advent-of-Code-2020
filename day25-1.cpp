#include <cmath>
#include <fstream>
#include <unordered_map>
#include <vector>

long long int transform(long long int subj, size_t loop_size)
{
  long long int res = 1;
  for (size_t i = 0; i < loop_size; ++i) {
    res *= subj;
    res %= 20201227;
  }
  return res;
}

size_t get_loop_size(long long int subj, long long int public_key, size_t mod)
{
  subj %= mod;
  public_key %= mod;

  int n = sqrt(mod) + 1;
  long long int an = transform(subj, n);

  std::unordered_map<long long int, long long int> vals;
  for (long long int q = 0, curr = public_key; q <= n; ++q) {
    vals[curr] = q;
    curr = (curr * subj) % mod;
  }

  for (long long int p = 1, curr = 1; p <= n; ++p) {
    curr = (curr * an) % mod;
    if (vals.find(curr) != vals.end()) {
      return n * p - vals[curr];
    }
  }
  return -1;
}

int main()
{
  std::ifstream input{"day25.in"};
  std::ofstream output{"day25-1.out"};

  std::string tmp;

  long long int card_pubkey, door_pubkey;
  getline(input, tmp);
  card_pubkey = std::stoll(tmp);
  getline(input, tmp);
  door_pubkey = std::stoll(tmp);

  output << transform(door_pubkey, get_loop_size(7, card_pubkey, 20201227))
         << std::endl;
}
