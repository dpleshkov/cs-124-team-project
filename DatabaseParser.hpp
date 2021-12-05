#ifndef CS124_TEAM_DATABASEPARSER_HPP
#define CS124_TEAM_DATABASEPARSER_HPP

#include "structures/Queue.hpp"
#include "structures/HashMap.hpp"
#include <fstream>
#include <sstream>
#include <vector>

struct Computer {
    std::string modelName;
    std::string brandName;
    double normalWattage = -1;
    double standbyWattage = -1;
    double maxWattage = -1;
};

int stringHash(std::string str) {
    int h = 0;
    for (char i : str) {
        h = 31 * h + i;
    }
    return std::abs(h % 65535);
}

class DatabaseParser {
public:
    explicit DatabaseParser(const std::string &filename) {
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line); // skip first line
        while (std::getline(file, line)) {
            Queue<char> buffer;
            Computer computer;
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
                    } else if (field == 2 && !data.empty()) {
                        std::cout << "Converting: " << data << std::endl;
                        computer.normalWattage = std::stod(data);
                    } else if (field == 3 && !data.empty()) {
                        std::cout << "Converting: " << data << std::endl;
                        computer.standbyWattage = std::stod(data);
                    } else if (field == 4 && !data.empty()) {
                        std::cout << "Converting: " << data << std::endl;
                        computer.maxWattage = std::stod(data);
                    }
                    field++;
                } else {
                    buffer.enqueue(c);
                }
            }
            computers.push_back(computer);
        }
    }

    HashMap<std::string, HashMap<std::string, Computer>*>* getHashMap() {
        auto output = new HashMap<std::string, HashMap<std::string, Computer>*>(stringHash, 200);
        for (const auto& computer : computers) {
            if (!(output -> exists(computer.brandName))) {
                auto models = new HashMap<std::string, Computer>(stringHash, 200);
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
    std::vector<Computer> computers;
};

#endif