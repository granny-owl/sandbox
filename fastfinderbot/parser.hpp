#pragma once
#include <vector>
#include <sstream>

using str_ref = const std::string&; 

std::vector<std::string> parse(str_ref str) {
    std::stringstream ss(str);
    std::string temp;
    std::vector<std::string> vec;
    while (std::getline(ss, temp, ' ')) {
        vec.push_back(temp);
    }
    return vec;
}

