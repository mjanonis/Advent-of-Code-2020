#include <execution>
#include <fstream>
#include <numeric>
#include <sstream>
#include <vector>

// CRT solver is taken from
// https://rosettacode.org/wiki/Chinese_remainder_theorem#C.2B.2B
template <typename _Ty> _Ty mulInv(_Ty a, _Ty b)
{
  _Ty b0 = b;
  _Ty x0 = 0;
  _Ty x1 = 1;

  if (b == 1) {
    return 1;
  }

  while (a > 1) {
    _Ty q = a / b;
    _Ty amb = a % b;
    a = b;
    b = amb;

    _Ty xqx = x1 - q * x0;
    x1 = x0;
    x0 = xqx;
  }

  if (x1 < 0) {
    x1 += b0;
  }

  return x1;
}

template <typename _Ty>
_Ty chineseRemainder(const std::vector<_Ty>& n, const std::vector<_Ty>& a)
{
  _Ty prod = std::reduce(std::execution::seq, n.begin(), n.end(), (_Ty)1,
                         [](_Ty a, _Ty b) { return a * b; });

  _Ty sm = 0;
  for (int i = 0; i < n.size(); i++) {
    _Ty p = prod / n[i];
    sm += a[i] * mulInv(p, n[i]) * p;
  }

  return sm % prod;
}

// Modulo operator that always returns a positive remainder
long long int mod(const long long int& lhs, const long long int& rhs)
{
  return (rhs + (lhs % rhs)) % rhs;
}

int main()
{
  std::ifstream input{"day13.in"};
  std::ofstream output{"day13-2.out"};

  std::string tmp;
  std::vector<int> busIDs;

  // Ignore first line
  getline(input, tmp);
  getline(input, tmp);
  std::istringstream iss(tmp);

  while (getline(iss, tmp, ',')) {
    if (tmp == "x") {
      busIDs.push_back(0);
      continue;
    }
    busIDs.push_back(std::stoi(tmp));
  }

  std::vector<long long int> n, a;
  for (auto x : busIDs) {
    if (x != 0) {
      n.push_back(x);
    }
  }

  for (int t = 0; t > -static_cast<int>(busIDs.size()); --t) {
    if (busIDs[-t] == 0) {
      continue;
    }
    a.push_back(mod(t, busIDs[-t]));
  }

  output << chineseRemainder(n, a) << std::endl;
}
