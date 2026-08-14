# DualScreen Survival Horror (Proof of Concept)

A lightweight C++17 telemetry reader designed to interface with RetroArch's Network Control Interface, targeting Resident Evil 2 (SLUS-00748) via the SwanStation core on Linux x86_64.

## Requirements
* Linux x86_64
* CMake 3.12+ & C++17 Compiler
* RetroArch 1.22.2 with Network Control Interface enabled on UDP port 55355

## Build & Run
```bash
mkdir build && cd build
cmake ..
make
./dualscreen_survival_horror
