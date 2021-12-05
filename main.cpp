#include <iostream>
#include "TPCDBDatabaseParser.hpp"

int main() {
    Computer comp;
    TPCDBDatabaseParser parser("../data/tpcdb.csv");
    auto consumptionDB = parser.getHashMap();
    std::cout << "Hello world" << std::endl;
}