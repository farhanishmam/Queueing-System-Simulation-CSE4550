cmake_minimum_required(VERSION 3.19)
project(MSQS_2_Servers_Scenario_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(MSQS_2_Servers_Scenario_2 main.cpp scheduler.cpp scheduler.h event.cpp event.h server.cpp server.h queue.cpp queue.h)