#include <bitset>
#include <fstream>
#include <string>

int main()
{
  std::ifstream input{"day04.in"};
  std::ofstream output{"day04-1.out"};

  std::string tmp;
  std::bitset<7> req_fields;
  size_t valid_passwords = 0;

  while (std::getline(input, tmp)) {
    if (tmp.find("byr") != std::string::npos) {
      req_fields.set(0);
    }
    if (tmp.find("iyr") != std::string::npos) {
      req_fields.set(1);
    }
    if (tmp.find("eyr") != std::string::npos) {
      req_fields.set(2);
    }
    if (tmp.find("hgt") != std::string::npos) {
      req_fields.set(3);
    }
    if (tmp.find("hcl") != std::string::npos) {
      req_fields.set(4);
    }
    if (tmp.find("ecl") != std::string::npos) {
      req_fields.set(5);
    }
    if (tmp.find("pid") != std::string::npos) {
      req_fields.set(6);
    }

    if (tmp.length() == 0) {
      if (req_fields.all()) {
        ++valid_passwords;
      }
      req_fields.reset();
    }
  }

  // To deal with the final entry
  if (req_fields.all()) {
    ++valid_passwords;
  }

  output << valid_passwords << std::endl;
}
