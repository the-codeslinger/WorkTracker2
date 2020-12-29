cmake_minimum_required(VERSION 3.16.3)

project(wt2-shared-test VERSION 2.0.0 DESCRIPTION "WorkTracker2 Shared Library Tests")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Test REQUIRED)

if (NOT TARGET wt2-shared)
    add_subdirectory(../wt2-shared build)
endif()

set(SOURCES
    main.cpp
    data/testdatasource.cpp
)

set(HEADERS
    testrunner.h
    data/testdatasource.h
)

set(INCLUDES
    ./
    data/
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Test wt2-shared)
