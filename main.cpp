#include <iostream>
#include "DatabaseParser.hpp"

int main() {
    DatabaseParser parser("../data/tpcdb.csv");
    auto consumptionDB = parser.getHashMap();
    std::cout << "Hello world" << std::endl;
}