cmake_minimum_required(VERSION 3.19)
project(MSQS_2_Servers_Scenario_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(MSQS_2_Servers_Scenario_1 main.cpp event.cpp event.h queue.cpp queue.h scheduler.cpp scheduler.h server.cpp server.h serviceFacility.cpp serviceFacility.h)