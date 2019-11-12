set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.cpp)
find_package (Threads)
set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})
# target_link_libraries (${BINARY} ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest_main)
