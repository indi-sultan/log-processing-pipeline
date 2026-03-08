<!--sample readme will update it later -->

# Multithreaded log processing pipeline

A high-performance log processing pipeline implemented in modern C++

## Features
- Multithreaded pipeline architecture
- Thread-safe queue
- Log parsing and filtering
- Aggregation of log statistics
- Built using CMake
- Unit tests included

## Pipeline Architecture

Reader -> Parser -> Filter -> Aggregator

# Build
cd build
cmake ..
make

- for pipeline run:
./log_pipeline

- for tests run:
./queue_test
