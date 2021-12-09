#include <iostream>
#include <vector>
#include <iomanip>
#include "structures/HashMap.hpp"
#include "TPCDBDatabaseParser.hpp"
#include "EnergyStarDatabaseParser.hpp"
#include "binary_search_tree.hpp"
#include "Search.hpp"
#include "stateInfo.hpp"

double calculate_kwh(double watts, int hrs) {
    return (watts * hrs) / 1000;
}

double calculate_pounds_CO2(State state, double kWh) {
    return kWh * ((state.coal * 2.23) + (state.oil * 2.13) + (state.naturalGas * 0.91));
}

int stateHashString(std::string str) {
    int h = 0;
    for (char i : str) {
        h = 31 * h + i;
    }
    return std::abs(h % 65535);
}

HashMap<std::string, State*>* state_usages() {
    auto map = new HashMap<std::string, State*>(stateHashString, 50);
    map -> set("Alabama", new State("Alabama", 0.19, 0.4, 0));
    map -> set("Alaska", new State("Alaska", 0.11, 0.5, 0.14));
    map -> set("Arizona", new State("Arizona", 0.2, 0.4, 0));
    map -> set("Arkansas", new State("Arkansas", 0.38, 0.33, 0));
    map -> set("California", new State("California", 0, 0.39, 0));
    map -> set("Colorado", new State("Colorado", 0.44, 0.3, 0));
    map -> set("Connecticut", new State("Connecticut", 0.01, 0.52, 0.01));
    map -> set("Delaware", new State("Delaware", 0.05, 0.89, 0.02));
    map -> set("Florida", new State("Florida", 0.09, 0.74, 0.01));
    map -> set("Georgia", new State("Georgia", 0.2, 0.45, 0));
    map -> set("Hawaii", new State("Hawaii", 0.12, 0, 0.62));
    map -> set("Idaho", new State("Idaho", 0, 0.21, 0));
    map -> set("Illinois", new State("Illinois", 0.27, 0.1, 0));
    map -> set("Indiana", new State("Indiana", 0.59, 0.31, 0));
    map -> set("Iowa", new State("Iowa", 0.35, 0.13, 0));
    map -> set("Kansas", new State("Kansas", 0.33, 0.7, 0));
    map -> set("Kentucky", new State("Kentucky", 0.73, 0.21, 0));
    map -> set("Louisiana", new State("Louisiana", 0.07, 0.69, 0.03));
    map -> set("Maine", new State("Maine", 0.01, 0.16, 0.01));
    map -> set("Maryland", new State("Maryland", 0.14, 0.37, 0.01));
    map -> set("Massachusetts", new State("Massachusetts", 0, 0.64, 0));
    map -> set("Michigan", new State("Michigan", 0.32, 0.29, 0.01));
    map -> set("Minnesota", new State("Minnesota", 0.31, 0.18, 0));
    map -> set("Mississippi", new State("Mississippi", 0.07, 0.74, 0));
    map -> set("Missouri", new State("Missouri", 0.73, 0.1, 0));
    map -> set("Montana", new State("Montana", 0.52, 0.02, 0.02));
    map -> set("Nebraska", new State("Nebraska", 0.55, 0.03, 0));
    map -> set("Nevada", new State("Nevada", 0.07, 0.64, 0));
    map -> set("New Hampshire", new State("New Hampshire", 0.02, 0.2, 0));
    map -> set("New Jersey", new State("New Jersey", 0.01, 0.55, 0));
    map -> set("New Mexico", new State("New Mexico", 0.41, 0.34, 0));
    map -> set("New York", new State("New York", 0, 0.37, 0.01));
    map -> set("North Carolina", new State("North Carolina", 0.23, 0.32, 0));
    map -> set("Norh Dakota", new State("Norh Dakota", 0.63, 0.03, 0));
    map -> set("Ohio", new State("Ohio", 0.39, 0.43, 0));
    map -> set("Oklahoma", new State("Oklahoma", 0.09, 0.53, 0));
    map -> set("Oregon", new State("Oregon", 0.02, 0.34, 0));
    map -> set("Pennsylvania", new State("Pennsylvania", 0.17, 0.42, 0));
    map -> set("Rhode Island", new State("Rhode Island", 0, 0.91, 0));
    map -> set("South Carolina", new State("South Carolina", 0.15, 0.24, 0));
    map -> set("South Dakota", new State("South Dakota", 0.21, 0.11, 0));
    map -> set("Tennessee", new State("Tennessee", 0.23, 0.2, 0));
    map -> set("Texas", new State("Texas", 0.19, 0.53, 0));
    map -> set("Utah", new State("Utah", 0.64, 0.24, 0));
    map -> set("Vermont", new State("Vermont", 0,0.001,0));
    map -> set("Virginia", new State("Virginia", 0.02, 0.59, 0));
    map -> set("Washington", new State("Washington", 0.07, 0.13, 0));
    map -> set("West Virginia", new State("West Virginia", 0.91, 0.01, 0));
    map -> set("Wisconsin", new State("Wisconsin", 0.42, 0.34, 0));
    map -> set("Wyoming", new State("Wyoming", 0.84, 0.01, 0));
    return map;
}

int main() {
    TPCDBComputer comp;
    TPCDBDatabaseParser parser("data/tpcdb.csv");
    auto consumptionDB = parser.getHashMap();
    EnergyStarDatabaseParser eparser("./data/EnergyStarParsed.csv");
    auto energyDB = eparser.getHashMap();
    BinarySearchTree recommender;
    for (auto brandName: energyDB->getKeys()) {
        auto models = energyDB->get(brandName);
        for (auto modelName: models->getKeys()) {
            EnergyStarComputer computer = models->get(modelName);
            if (computer.type == "Notebook") {
                recommender.insert(computer);
            }
        }
    }

    std::string menu;
    
    std::string type_of_usage;
    double hours = 0;

    auto states = state_usages();

    while (menu != "q")
     {
      std::string choice = "";
      std::cout << "\n<< Main Menu >>\n";
        std::cout << "\nPlease pick an option from the list \n1. Calculator\n2. Laptop Compare (Energy Star)\n'q' to quit: ";
        menu = "";
        getline(std::cin, menu);
        if (menu == "1") {
          while(choice != "q")
          {
            std::cout << "\n<< Laptop kwH Calculator >>\n";
            std::cout
                    << "\nDo you play games (enter \"games\") or just casually use your computer (enter \"casual\")?\n'q' to go back: ";
            getline(std::cin, type_of_usage);
            if(type_of_usage == "q")
            {
              break;
            }
            bool successful_calculation = 0;
            std::cout << "\nHow many hours do you spend daily on your computer?\n";
            std::cin >> hours;
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            auto tpc = findTPCDBComputer(consumptionDB);
            double kwh =0;
            if (type_of_usage == "games") {
                if (tpc.maxWattage != -1) {
                    std::cout << "\n" << tpc.modelName << ": ";
                    kwh = calculate_kwh(tpc.maxWattage, hours);
                    std::cout << "\nkwH = " << kwh << "\n";
                    successful_calculation = 1;
                } else {
                    std::cout << "\nError";
                    std::cout << "\nDatabase doesn't have the max wattage listed.\n";

                }
            } else {
                if (tpc.normalWattage != -1) {
                  kwh = calculate_kwh(tpc.normalWattage, hours);
                  std::cout << "\nkwH = " << kwh << "\n";
                  successful_calculation = 1;
                }
                else{
                  std::cout << "\nError";
                  std::cout << "\nDatabase doesn't have the normal wattage listed.\n";
                }
            }
            std::string state;
            if(successful_calculation){
            std::cout << "\nWhat state do you live in?\n> ";
            getline(std::cin, state);
            std::cout << "To generate the " << kwh << " kWh of energy powering your computer, an estimated " << calculate_pounds_CO2(*(states -> get(state)), kwh) << " pounds of carbon dioxide get released into the atmosphere.\n";
            
            }
          }
        } 
        if (menu == "2") {
          while(choice != "q")
          {
            
            int energyStar_kwh = 0;
            bool userinputted = 0;
            
            std::cout << "\n<< Laptop Compare >>\n";
            std::cout << "\nPlease pick an option from the list \n1. Compare your laptop\n2. Manually enter kwH\n'q' to go back: ";
            
            getline(std::cin,choice);
            std::string userLaptop;
            if(choice == "1")
            {
              auto energystar = findEnergyStarComputer(energyDB);
              userLaptop = energystar.modelName;
              energyStar_kwh = energystar.tecKWH;
              userinputted = 1;
            }
            if(choice == "2")
            {
              std::cout << "\nEnter TEC kwH: ";
              std::cin >> energyStar_kwh;
              std::cin.clear();
              std::cin.ignore(1000,'\n');
              userinputted = 1;
            }
            double maxRange = recommender.find(1000).tecKWH;
            double minRange = recommender.find(-1).tecKWH;
            int brandw = 15;
            int modelw = 40;
            int datew = 20;
            int tecw = 20;
            if(choice == "1")
            {
              std::cout << "\n\nYour laptop: " << userLaptop << " TEC kwh: "<< energyStar_kwh;
            }
            if(userinputted)
            {
              std::cout << "\n(Here are laptops that have a lower TEC kwH than your listed TEC kwH)\n";
              std::cout << std::left << std::setw(brandw) << std::setfill(' ') << "Brand" << std::left
                        << std::setw(modelw) << "Model Name" << std::left << std::setw(datew) << "Date" << "TEC kwH";
              std::cout << "\n==================================================================================\n";
              for (int i = 0; i < 10; i++) {

                  if (energyStar_kwh > maxRange) {
                      energyStar_kwh = maxRange;
                  } else if (energyStar_kwh < minRange) {
                      energyStar_kwh = minRange;
                  }
                  auto suggestion = recommender.find(energyStar_kwh);

                  if (suggestion.tecKWH != -1) {
                      std::cout << std::left << std::setw(brandw) << std::setfill('-') << suggestion.brandName
                                << std::left << std::setw(modelw) << suggestion.modelName << std::left << std::setw(datew)
                                << suggestion.dateOnMarket << suggestion.tecKWH << "\n";
                      energyStar_kwh -= 3;
                  }
                  else
                  {
                      std::cout << "No more laptops found\n";
                    break;
                  }
              }
            }
          }
        }
        std::cin.clear();
        
    } 
    std::cout << "\nGoodbye!";
}