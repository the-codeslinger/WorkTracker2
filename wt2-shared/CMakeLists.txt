cmake_minimum_required(VERSION 3.16.0)

project(wt2-shared VERSION 2.0.0 DESCRIPTION "WorkTracker2 Shared Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

add_compile_definitions(WT2_LIBRARY)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)

include_directories(include/)

add_library(${PROJECT_NAME} 
    src/core/duration.cpp
    src/core/logging.cpp
    src/data/datasource.cpp
    src/data/sql/sqldatasource.cpp
    src/model/task.cpp
    src/model/timeslot.cpp
    src/model/workday.cpp
    src/model/worktask.cpp
)

target_link_libraries(wt2-shared Qt6::Core Qt6::Sql)
