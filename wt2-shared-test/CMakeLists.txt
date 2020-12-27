cmake_minimum_required(VERSION 3.16.3)

project(wt2-shared-test VERSION 2.0.0 DESCRIPTION "WorkTracker2 Shared Library Tests")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Test REQUIRED)

if (NOT TARGET wt2-shared)
    add_subdirectory(../wt2-shared build)
endif()

include_directories(
    ./
    data/
)

add_executable(${PROJECT_NAME} 
    main.cpp
    data/testdatasource.cpp
)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Test wt2-shared)
