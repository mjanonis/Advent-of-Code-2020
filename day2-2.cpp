#include <fstream>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream input{"day2.in"};
    std::ofstream output{"day2-2.out"};

    std::string tmp;
    unsigned int valid_pwords = 0;

    while(std::getline(input, tmp)){

        size_t min = std::stoi(tmp.substr(0, tmp.find('-')));
        size_t max = std::stoi(tmp.substr(tmp.find('-')+1));
        char ch = tmp.at(tmp.find(' ')+1);
        std::string pword = tmp.substr(tmp.find(':')+2);

        // XOR comparison
        if(!(pword.at(min-1)==ch) != !(pword.at(max-1)==ch)){
            ++valid_pwords;
        }
    }

    output << valid_pwords << std::endl;

}
