cmake_minimum_required(VERSION 3.28)
project(ArithmeticExpressionParser LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(parser
    src/parser/parser.cpp 
    src/parser/token.cpp 
)
target_compile_features(parser PRIVATE cxx_std_17)
target_include_directories(parser PUBLIC include/parser)

add_executable(my_test test/mytest.cpp)
target_compile_features(my_test PRIVATE cxx_std_17)
target_include_directories(my_test PUBLIC include/parser)
target_link_libraries(my_test PUBLIC parser)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC include/parser)
target_link_libraries(${PROJECT_NAME} parser)

add_test(test_0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/my_test 
    "1+ 1425+48-2312.67 *3" "-5464.01"
    "1+1" "2"
)
add_test(test_1 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/my_test 
    "1+1"
    "2"
)
add_test(test_2 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/my_test 
    "1+1*5"
    "6"
)
add_test(test_3 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/my_test 
    "+1"
    "1"
)





