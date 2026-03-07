cmake_minimum_required(VERSION 3.28)

project(LogProcessingPipeline VERSION 1.0 LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/reader.cpp
    src/parser.cpp
    src/filter.cpp
    src/aggregator.cpp
)

# Create executable
add_executable(log_pipeline ${SOURCES})

# Thread support
find_package(Threads REQUIRED)
target_link_libraries(log_pipeline PRIVATE Threads::Threads)

# -------- Tests --------
enable_testing()

add_executable(queue_test
    tests/queue_test.cpp
)

target_link_libraries(queue_test PRIVATE Threads::Threads)

add_test(NAME QueueTest COMMAND queue_test)