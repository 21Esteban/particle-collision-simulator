cmake_minimum_required(VERSION 3.16)

project(ParticleCollisionSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(particle_simulation
    src/main.cpp
    src/particle.h src/particle.cpp
    src/obstacle.h src/obstacle.cpp
    src/simulation.h src/simulation.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(particle_simulation PRIVATE -Wall -Wextra -Wpedantic)
endif()
