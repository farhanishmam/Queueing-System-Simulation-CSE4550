cmake_minimum_required(VERSION 3.19)
project(Soruce_Code)

set(CMAKE_CXX_STANDARD 20)

add_executable(Soruce_Code main.cpp event.cpp event.h queue.cpp queue.h scheduler.cpp scheduler.h server.cpp server.h serviceFacility.cpp serviceFacility.h)