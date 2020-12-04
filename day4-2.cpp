#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <map>

bool is_valid(const std::string& key, const std::string& value){
    if(key == "byr"){
        if(value.length() == 4 && std::stoi(value)>=1920 && std::stoi(value)<=2002){return true;}
        return false;
    }
    if(key == "iyr"){
        if(value.length() == 4 && std::stoi(value)>=2010 && std::stoi(value)<=2020){return true;}
        return false;
    }
    if(key == "eyr"){
        if(value.length() == 4 && std::stoi(value)>=2020 && std::stoi(value)<=2030){return true;}
        return false;
    }
    if(key == "hgt"){
        std::string unit = value.substr(value.length() - 2);
        std::string height = value.substr(0, value.length() - 2);
        if(unit=="cm" && std::stoi(height) >=150 && std::stoi(height) <= 193){return true;}
        if(unit=="in" && std::stoi(height)>=59 && std::stoi(height)<=76){return true;}
        return false;
    }
    if(key == "hcl"){
        if(value.length() == 7 && value[0]=='#' && isxdigit(value[1]) &&
           isxdigit(value[1]) && isxdigit(value[2]) && isxdigit(value[3]) &&
           isxdigit(value[4]) && isxdigit(value[5]) && isxdigit(value[6])){return true;}
        return false;
    }
    if(key == "ecl"){
        if(value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" ||
           value == "hzl" || value == "oth"){return true;}
        return false;
    }
    if(key == "pid"){
        if(value.length() == 9 && isdigit(value[0]) && isdigit(value[1]) && isdigit(value[2]) &&
           isdigit(value[3]) && isdigit(value[4]) && isdigit(value[5]) && isdigit(value[6]) &&
           isdigit(value[7]) && isdigit(value[8])){return true;}
        return false;
    }
    return false;
}

int main(){
    std::ifstream input{"day4.in"};
    std::ofstream output{"day4-2.out"};

    std::string tmp, kv;
    std::bitset<7> req_fields;
    size_t valid_passwords = 0;

    // Map that holds key, position in bitfield pairs
    std::map<std::string, size_t> ktb;
    ktb["byr"] = 0;
    ktb["iyr"] = 1;
    ktb["eyr"] = 2;
    ktb["hgt"] = 3;
    ktb["hcl"] = 4;
    ktb["ecl"] = 5;
    ktb["pid"] = 6;

    while(std::getline(input, tmp)){
        std::stringstream ss(tmp);

        while(ss >> kv){
            std::string key = kv.substr(0, kv.find(':'));
            std::string value = kv.substr(kv.find(':')+1, kv.size());
            if(key=="cid"){continue;}
            req_fields.set(ktb[key], is_valid(key, value));
        }

        if(tmp.length()==0){
            if(req_fields.all()){++valid_passwords;}
            req_fields.reset();
        }
    }

    // To deal with the final entry
    if(req_fields.all()){++valid_passwords;}

    output << valid_passwords << std::endl;
}
