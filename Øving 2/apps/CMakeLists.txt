cmake_minimum_required(VERSION 3.12)

project(YourProjectName)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files
add_executable(main main.cpp ../src/Workers.cpp)

# Include directories
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find threads package (required for std::thread)
find_package(Threads REQUIRED)

# Link the threads library
target_link_libraries(main PRIVATE Threads::Threads)
