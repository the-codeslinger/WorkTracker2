cmake_minimum_required(VERSION 3.16.3)
project(WorkTracker2)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(wt2-shared)
add_subdirectory(wt2-shared-test)
