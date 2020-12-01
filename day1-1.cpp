#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

int main()
{
    std::ifstream input{"day1.in"};
    std::ofstream output{"day1-1.out"};

    std::vector<int> numbers;
    std::unordered_map<int, int> hmap;
    int tmp;

    while(input >> tmp){
        numbers.push_back(tmp);
    }

    for(size_t i = 0; i < numbers.size(); ++i){
        if(hmap.find(2020 - numbers[i]) != hmap.end()){
            output << numbers[hmap[2020 - numbers[i]]] * numbers[i] << '\n';
        }
        hmap[numbers[i]] = i;
    }

}
