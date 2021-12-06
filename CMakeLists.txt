cmake_minimum_required(VERSION 3.20)
project(cs_124_team_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs_124_team_project structures/Stack.hpp structures/HashMap.hpp structures/Queue.hpp TPCDBDatabaseParser.hpp EnergyStarDatabaseParser.hpp main.cpp)
