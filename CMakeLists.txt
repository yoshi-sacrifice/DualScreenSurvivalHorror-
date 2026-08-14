cmake_minimum_required(VERSION 3.12)
project(DualScreenSurvivalHorror VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(dualscreen_survival_horror
    src/main.cpp
    src/retroarch_client.cpp
    src/re2_telemetry.cpp
)
