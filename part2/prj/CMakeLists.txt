cmake_minimum_required(VERSION 3.0)
project(drone)
include_directories(inc)
file(GLOB SOURCE "src/*.cpp" "inc/*.hh")
add_executable(${PROJECT_NAME} ${SOURCE})
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++1z")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
