cmake_minimum_required(VERSION 3.10)

project(PrimeNumberFinderWithThreads CXX)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the executable target
add_executable(PrimeNumberFinderWithThreads PrimeNumberFinderWithThreads.cpp)
