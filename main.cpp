#include <iostream>
#include "DatabaseParser.hpp"

int main() {
    DatabaseParser parser("../data/tpcdb.csv");
    parser.getHashMap();
    std::cout << "Hello world" << std::endl;
}