cmake_minimum_required (VERSION 2.8)

project(matrix_calculator)

add_definitions('-Wall')

set(SOURCES
    src/main.cpp
    src/matrix.cpp
    src/system.cpp
    include/matrix.hpp
    include/system.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
    PRIVATE src/ include/
)
