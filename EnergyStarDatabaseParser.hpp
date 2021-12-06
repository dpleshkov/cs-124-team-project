#ifndef CS124_TEAM_ENERGYSTAR_DATABASEPARSER_HPP
#define CS124_TEAM_ENERGYSTAR_DATABASEPARSER_HPP

#include "structures/Queue.hpp"
#include "structures/HashMap.hpp"
#include <fstream>
#include <sstream>
#include <vector>

struct EnergyStarComputer {
    std::string modelName;
    std::string brandName;
    std::string modelNumber;
    std::string type;
    double sleepWattage = -1;
    double longIdleWattage = -1;
    double shortIdleWattage = -1;
    double tecKWH = -1;
};

int energyStarStringHash(std::string str) {
    int h = 0;
    for (char i : str) {
        h = 31 * h + i;
    }
    return std::abs(h % 65535);
}

class EnergyStarDatabaseParser {
public:
    explicit EnergyStarDatabaseParser(const std::string &filename) {
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line); // skip first line
        while (std::getline(file, line)) {
            Queue<char> buffer;
            EnergyStarComputer computer;
            int field = 0;
            for (char c: line) {
                if (c == '|') {
                    std::string data;
                    while (!buffer.isEmpty()) {
                        data += buffer.peek();
                        buffer.dequeue();
                    }
                    if (field == 0) {
                        computer.brandName = data;
                    } else if (field == 1) {
                        computer.modelName = data;
                    } else if (field == 2) {
                        computer.modelNumber = data;
                    } else if (field == 3) {
                        computer.type = data;
                    } else if (field == 4 && !data.empty()) {
                        computer.sleepWattage = std::stod(data);
                    } else if (field == 5 && !data.empty()) {
                        computer.longIdleWattage = std::stod(data);
                    } else if (field == 6 && !data.empty()) {
                        computer.shortIdleWattage = std::stod(data);
                    } else if (field == 7 && !data.empty()) {
                        computer.tecKWH = std::stod(data);
                    }
                    field++;
                } else {
                    buffer.enqueue(c);
                }
            }
            computers.push_back(computer);
        }
    }

    HashMap<std::string, HashMap<std::string, EnergyStarComputer>*>* getHashMap() {
        auto output = new HashMap<std::string, HashMap<std::string, EnergyStarComputer>*>(energyStarStringHash, 200);
        for (const auto& computer : computers) {
            if (!(output -> exists(computer.brandName))) {
                auto models = new HashMap<std::string, EnergyStarComputer>(energyStarStringHash, 200);
                output -> set(computer.brandName, models);
                models -> set(computer.modelName, computer);
            } else {
                auto models = output -> get(computer.brandName);
                models -> set(computer.modelName, computer);
            }
        }
        return output;
    }

private:
    std::vector<EnergyStarComputer> computers;
};

#endif