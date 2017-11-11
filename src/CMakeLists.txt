cmake_minimum_required (VERSION 2.6)
project (Neuron)

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(neuron neuron.cpp twoneurons.cpp network.cpp main.cpp)
add_executable(unit_test neuron.cpp twoneurons.cpp network.cpp unitTest.cpp)
target_link_libraries(unit_test gtest gtest_main)
add_test(unit_test unit_test)
