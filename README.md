# 🚀 Multithreaded Log Processing Pipeline (C++)

## 📌 Overview

This project is a **high-performance, multithreaded log processing pipeline** built in modern C++. It is designed to simulate real-world backend systems that process large volumes of log data efficiently and reliably.

The pipeline follows a **producer-consumer architecture** with multiple stages, each running in separate threads and communicating through thread-safe queues.

The primary goal of this project is to demonstrate:

* Strong understanding of **multithreading and concurrency**
* Use of **thread-safe data structures**
* Design of **scalable pipeline architectures**
* Clean and modular **C++ system design**
* Practical knowledge of **synchronization primitives**

---

## 🏗️ Architecture

The pipeline is divided into multiple stages:

```
Log Source → Reader → Parser → Filter → Aggregator → Output
```

Each stage runs independently and communicates via **thread-safe queues**.

### 🔹 1. Reader Stage

* Reads raw log lines from a file
* Pushes each log entry into a queue
* Typically runs as a **single thread** (I/O bound)

### 🔹 2. Parser Stage

* Converts raw log strings into structured data
* Example fields:

  * Timestamp
  * Log Level (INFO, ERROR, etc.)
  * Message
* Uses a **thread pool (e.g., 4–8 threads)** for parallel processing

### 🔹 3. Filter Stage

* Filters logs based on conditions

  * Example: Only ERROR logs
* Helps reduce unnecessary downstream processing

### 🔹 4. Aggregator Stage

* Performs computations like:

  * Counting log levels
  * Frequency analysis
* Maintains shared state (requires synchronization)

### 🔹 5. Output Stage

* Displays or stores processed results
* Can be extended to:

  * Write to files
  * Send over network
  * Store in database

---

## ⚙️ Key Features

### ✅ Multithreading

* Uses `std::thread`
* Thread pools for CPU-bound stages
* Efficient utilization of CPU cores

### ✅ Thread-Safe Queue

Custom implementation using:

* `std::mutex`
* `std::condition_variable`

Ensures:

* Safe communication between threads
* Blocking wait for producers/consumers

### ✅ Modular Design

* Each stage is independent
* Easy to extend or replace components

### ✅ Scalable Pipeline

* Supports increasing workload by:

  * Adding more worker threads
  * Adjusting queue sizes

### ✅ Clean Project Structure

```
log-processing-pipeline/
│
├── include/              # Header files
│   └── pipeline/
│       ├── thread_safe_queue.h
│       ├── reader.h
│       ├── parser.h
│       ├── filter.h
|       ├── log_entry.h
│       ├── aggregator.h
│
├── src/                  # Source files
│   ├── reader.cpp
│   ├── parser.cpp
│   ├── filter.cpp
│   ├── aggregator.cpp
|   ├── main.cpp
│
├── tests/                # Test file
│   ├── queue_test.cpp
│
├── logs/                 # Sample log files
│   └── sample.log
│
├── CMakeLists.txt
├── LICENSE
├── .gitignore
├── build/
└── README.md
```

---

## 🧵 Threading Model

| Stage      | Thread Type   | Count |
| ---------- | ------------- | ----- |
| Reader     | Single thread | 1     |
| Parser     | Thread pool   | 4–8   |
| Filter     | Thread pool   | 2–4   |
| Aggregator | Single thread | 1     |
| Output     | Single thread | 1     |

### Why this design?

* Reader is I/O-bound → no need for many threads
* Parser is CPU-heavy → parallelize
* Aggregator requires shared state → controlled threading

---

## 🔄 Data Flow

1. Reader reads logs → pushes to Queue A
2. Parser threads consume Queue A → push to Queue B
3. Filter consumes Queue B → pushes to Queue C
4. Aggregator processes Queue C
5. Output displays final results

---

## 🧪 Testing Strategy

### ✔️ Integration Testing (Primary)

* Validate full pipeline:

  ```
  File → Reader → Queue → Processing
  ```

### ✔️ Unit Testing

* Thread-safe queue tested independently
* Ensures:

  * No race conditions
  * Correct blocking behavior

---

## 🛠️ Build Instructions

### Prerequisites

* C++17 or later
* CMake (≥ 3.10)
* GCC / Clang

### Build Steps

```bash
git clone <repo-url>
cd log-processing-pipeline

mkdir build
cd build

cmake ..
make
```

### Run

```bash
./log_pipeline
```

---

## 📈 Performance Considerations

* Avoid excessive thread creation
* Use **bounded queues** to prevent memory overflow
* Balance thread count with CPU cores
* Minimize lock contention

---

## 💡 Key Learnings

This project demonstrates:

* Real-world use of **producer-consumer pattern**
* Designing **high-throughput systems**
* Managing **race conditions and synchronization**
* Structuring large-scale C++ applications

---

## 📚 Tech Stack

* **Language:** C++17
* **Concurrency:** std::thread, mutex, condition_variable
* **Build System:** CMake
* **Testing:** GoogleTest

---

## 🤝 Contribution

Contributions are welcome. Feel free to:

* Add new pipeline stages
* Improve performance
* Enhance testing coverage

---

## 📜 License

This project is for educational and demonstration purposes.

---

## 👨‍💻 Author

Shivam \
System Engineer

---
