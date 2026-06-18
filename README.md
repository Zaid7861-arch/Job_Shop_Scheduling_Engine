# Event-Driven Task Scheduling Engine

[![C++](https://img.shields.io/badge/C++-11%2B-blue.svg)](https://isocpp.org/)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Overview
A high-performance, event-driven task scheduler engineered in C++ to optimize workload distribution across multiple concurrent processors. Designed to simulate complex job-shop scheduling scenarios, this engine features dynamic preemption, custom memory management, and timeline fast-forwarding, strictly bounded to an **O(n log n)** time complexity.

## Key Features
* **Custom Min-Heap Implementation:** A generic, array-based priority queue built from scratch using Floyd’s Heap-Building Algorithm for **O(n)** initialization.
* **Dynamic Preemption:** Seamlessly pauses and resumes mid-process tasks when higher-priority events occur, recalculating task priority dynamically based on real-time remaining workloads.
* **Event-Driven Timeline:** Utilizes relative time-delta (`dt`) calculations to "fast-forward" simulations, efficiently processing idle gaps without the overhead of tick-by-tick looping.
* **O(1) Load Balancing Forecasts:** The central manager maintains a live, memory-safe forecast of processor availability, assigning incoming tasks to the optimal node in **O(log m + log n)** time.

## System Architecture

The engine is modularized into four core components:

* `heap.cpp` **(The Sorting Engine):** A heavily templated custom priority queue utilizing `std::function` for dynamic lambda comparators and safe pass-by-reference memory handling.
* `treasure.cpp` **(Task Representation):** The data structure defining raw materials/jobs, tracking arrival times, original size, and live remaining workloads.
* `crewmate.cpp` **(Worker Node / Processor):** Acts as an interrupt-driven state machine. Manages individual processing queues and executes the physics logic for timeline fast-forwarding.
* `straw_hat.cpp` **(Central Dispatcher):** The global load balancer. Evaluates real-time machine states and dispatches jobs to minimize overall system idle time.

## Getting Started

### Prerequisites
* A standard C++ compiler (GCC, Clang, or MSVC) supporting C++11 or higher.

### Compilation & Execution
To compile the engine locally, clone the repository and build the source via terminal:

```bash
# Clone the repository
git clone [https://github.com/Zaid7861-arch/Job_Shop_Scheduling_Engine.git](https://github.com/Zaid7861-arch/Job_Shop_Scheduling_Engine.git)

# Navigate to the directory
cd Job_Shop_Scheduling_Engine

# Compile the project
g++ main.cpp -o scheduler -std=c++11

# Run the executable
./scheduler
