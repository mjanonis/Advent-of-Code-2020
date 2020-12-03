#include <fstream>
#include <string>
#include <vector>

int main(){
    std::ifstream input{"day3.in"};
    std::ofstream output{"day3-1.out"};

    std::vector<std::string> map;
    std::string tmp;
    size_t tree_count = 0;

    while(std::getline(input, tmp)){
        map.push_back(tmp);
    }

    int x = 0;
    for(size_t i = 1; i < map.size(); ++i){
        x+=3;
        x %= map[0].length();
        if(map[i].at(x) == '#'){ ++tree_count; }
    }

    output << tree_count << std::endl;

}
