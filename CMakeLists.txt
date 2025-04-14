cmake_minimum_required(VERSION 3.28)
project(ArithmeticExpressionParser VERSION 0.1 LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(parser
    src/parser/parser.cpp 
    
    src/parser/token_evaluate.cpp
    src/parser/token_reduce.cpp
    src/parser/token_tree_view.cpp
    src/parser/token.cpp

)
target_compile_features(parser PRIVATE cxx_std_17)
target_include_directories(parser PUBLIC include/parser)

add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_include_directories(main PUBLIC include/parser)
target_link_libraries(main PRIVATE parser)




add_executable(evaluate_test test/evaluate_test.cpp)
target_compile_features(evaluate_test PRIVATE cxx_std_17)
target_include_directories(evaluate_test PUBLIC include/parser)
target_link_libraries(evaluate_test PRIVATE parser)

add_test(evaluate_test_0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/evaluate_test 
    "1+ 1425+48-2312.67 *3" "-5464.01"
    "1+1" "2"
)
add_test(evaluate_test_1 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/evaluate_test 
    "1+1"
    "2"
)
add_test(evaluate_test_2 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/evaluate_test 
    "1+1*5"
    "6"
)
# add_test(test_3 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/evaluate_test 
#     "+1"
#     "1"
# )

add_executable(parser_test test/parser_test.cpp)
target_compile_features(parser_test PRIVATE cxx_std_17)
target_include_directories(parser_test PUBLIC include/parser)
target_link_libraries(parser_test PRIVATE parser)

add_test(parser_test_0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/parser_test "1+(1425+(48))-2312.67 *3")






