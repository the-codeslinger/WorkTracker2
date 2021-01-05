cmake_minimum_required(VERSION 3.16.3)

project(wt2-shared VERSION 2.0.0 DESCRIPTION "WorkTracker2 Shared Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_AUTOMOC ON)

add_compile_definitions(WT2_LIBRARY)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)

set(SOURCES
    src/core/duration.cpp
    src/core/logging.cpp
    src/data/datasource.cpp
    src/data/sql/sqldatasource.cpp
    src/model/task.cpp
    src/model/timeslot.cpp
    src/model/workday.cpp
    src/model/worktask.cpp
)

set(HEADERS
    include/worktracker2_global.h
    include/core/constants.h
    include/core/duration.h
    include/core/helper.h
    include/core/logging.h
    include/data/datasource.h
    include/data/taskrepository.h
    include/data/workdayrepository.h
    include/data/sql/sqldatasource.h
    include/data/sql/sqltaskrepository.h
    include/model/task.h
    include/model/timeslot.h
    include/model/workday.h
    include/model/worktask.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

message(STATUS "BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}")

target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_link_libraries(wt2-shared Qt6::Core Qt6::Sql)
