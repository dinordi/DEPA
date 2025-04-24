cmake_minimum_required(VERSION 3.10)

# Project naam en versie
project(CircuitSimulator VERSION 1.0)

# C++17 standaard gebruiken
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Alle header bestanden in src map
include_directories(${PROJECT_SOURCE_DIR}/src)

# Voeg de source bestanden toe aan de executable
add_executable(CircuitSimulator 
    src/main.cpp
    src/Circuit.cpp
    src/InputFileHandler.cpp
)

# Controleer of we op Apple platform draaien
if(APPLE)
    # Specifieke settings voor macOS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Voeg een target toe om een directory te maken voor testcircuits
add_custom_target(
    create_test_directory
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/test_circuits
)

# Maak het aanmaken van de test directory een afhankelijkheid van de build
add_dependencies(CircuitSimulator create_test_directory)