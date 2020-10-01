cmake_minimum_required(VERSION 3.16.0)

project(worktrackershared VERSION 2.0.0 DESCRIPTION "WorkTracker2 Shared Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

add_compile_definitions(WT2_LIBRARY)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Xml REQUIRED)

include_directories(include/)

add_library(${PROJECT_NAME} 
    src/core/duration.cpp
    src/data/xml/xmldatasource.cpp
    src/data/xml/xmlrepository.cpp
    src/data/xml/xmltaskrepository.cpp
    src/data/xml/xmlworkdayrepository.cpp
    src/model/task.cpp
    src/model/timeslot.cpp
    src/model/workday.cpp
    src/model/worktask.cpp
)

target_link_libraries(worktrackershared Qt5::Core Qt5::Xml)