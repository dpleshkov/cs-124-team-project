#ifndef CS124_TEAM_SEARCH_HPP
#define CS124_TEAM_SEARCH_HPP

#include <iostream>
#include <vector>
#include "EnergyStarDatabaseParser.hpp"
#include "TPCDBDatabaseParser.hpp"

// Calculates the Levenshtein distance between 2 strings.
// Number of deletions, substitutions, or insertions needed to get from a to b
// Function written by GitHub Copilot, not us
int levenshteinDistance(std::string a, std::string b) {
    int m = static_cast<int>(a.length());
    int n = static_cast<int>(b.length());
    int d[m+1][n+1];
    for (int i = 0; i <= m; i++) {
        d[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        d[0][j] = j;
    }
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (a[i-1] == b[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else {
                d[i][j] = std::min(d[i-1][j-1], std::min(d[i-1][j], d[i][j-1])) + 1;
            }
        }
    }
    return d[m][n];
}

std::vector<std::string> closest5(std::vector<std::string> words, const std::string& query) {
    std::vector<std::string> output;
    for (int i = 0; i < 5; i++) {
        int min = 100;
        int min_index = 0;
        for (int j = 0; j < words.size(); j++) {
            int distance = levenshteinDistance(words[j], query);
            if (distance < min) {
                min = distance;
                min_index = j;
            }
        }
        output.push_back(words[min_index]);
        words.erase(words.begin() + min_index);
    }
    return output;
}

EnergyStarComputer findEnergyStarComputer(HashMap<std::string, HashMap<std::string, EnergyStarComputer>*>* energyDB) {
    std::string input;
    std::cout << "Please enter the brand name" << std::endl;
    std::cout << "> ";
    getline(std::cin, input);
    auto closestMatches = closest5(energyDB -> getKeys(), input);
    std::cout << "Pick an option from the list:" << std::endl;
    int count = 1;
    for (auto match : closestMatches) {
        std::cout << count << " : " << match << std::endl;
        count++;
    }
    std::cout << "> ";
    int choice;
    getline(std::cin, input);
    choice = std::stoi(input);
    auto models = energyDB -> get(closestMatches[choice-1]);
    std::cout << "Please enter the model name" << std::endl;
    std::cout << "> ";
    getline(std::cin, input);
    closestMatches = closest5(models -> getKeys(), input);
    std::cout << "Pick an option from the list:" << std::endl;
    count = 1;
    for (auto match : closestMatches) {
        std::cout << count << " : " << match << std::endl;
        count++;
    }
    std::cout << "> ";
    getline(std::cin, input);
    choice = std::stoi(input);
    auto computer = models -> get(closestMatches[choice-1]);
    return computer;
}

TPCDBComputer findTPCDBComputer(HashMap<std::string, HashMap<std::string, TPCDBComputer>*>* energyDB) {
    std::string input;
    std::cout << "Please enter the brand name" << std::endl;
    std::cout << "> ";
    getline(std::cin, input);
    auto closestMatches = closest5(energyDB -> getKeys(), input);
    std::cout << "Pick an option from the list:" << std::endl;
    int count = 1;
    for (auto match : closestMatches) {
        std::cout << count << " : " << match << std::endl;
        count++;
    }
    std::cout << "> ";
    int choice;
    getline(std::cin, input);
    choice = std::stoi(input);
    auto models = energyDB -> get(closestMatches[choice-1]);
    std::cout << "Please enter the model name" << std::endl;
    std::cout << "> ";
    getline(std::cin, input);
    closestMatches = closest5(models -> getKeys(), input);
    std::cout << "Pick an option from the list:" << std::endl;
    count = 1;
    for (auto match : closestMatches) {
        std::cout << count << " : " << match << std::endl;
        count++;
    }
    std::cout << "> ";
    getline(std::cin, input);
    choice = std::stoi(input);
    auto computer = models -> get(closestMatches[choice-1]);
    return computer;
}

#endif