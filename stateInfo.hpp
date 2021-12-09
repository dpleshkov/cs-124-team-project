#ifndef CS124_TEAM_STATEINFO_HPP
#define CS124_TEAM_STATEINFO_HPP

#include <string>

class State {
public:
  State(std::string name, double c, double g, double o);
  double coal;
  double naturalGas;
  double oil;
  std::string stateName;
};

State::State(std::string name, double c, double g, double o) {
    stateName = name;
    coal = c;
    naturalGas = g;
    oil = o;
}

/*State::State() {
  for(int i = 0; i < 50; i++){
    table[i] = nullptr;
  }
}*/

#endif
