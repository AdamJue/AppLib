//
// Created by yunti on 24-11-20.
//

#include <iostream>
#include <ExtendLib.h>
#include <string>

using namespace std;

int main() {
    std::cout << "Hello World!" << std::endl;

    auto res = ExtendLib::processFile("../res/result.txt");

    std::cout << "file content: " << res << std::endl;

    return 0;
}