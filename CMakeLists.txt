cmake_minimum_required (VERSION 2.8)

project(matrix_calculator)

add_definitions('-Wall')

set(SOURCES
    src/main.cpp
    src/matrix.cpp
    include/matrix.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(${PROJECT_NAME}
    PRIVATE src/ include/
)
