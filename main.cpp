#include <iostream>
#include "TPCDBDatabaseParser.hpp"
#include "EnergyStarDatabaseParser.hpp"

int main() {
    Computer comp;
    TPCDBDatabaseParser parser("../data/tpcdb.csv");
    auto consumptionDB = parser.getHashMap();
    EnergyStarDatabaseParser eparser("../data/EnergyStarParsed.csv");
    auto energyDB = parser.getHashMap();
    std::cout << "Hello world" << std::endl;
}