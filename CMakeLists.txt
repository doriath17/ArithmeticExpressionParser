cmake_minimum_required(VERSION 3.28)
project(ArithmeticExpressionParser LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/parser/parser.cpp
    src/expr-token/token.cpp
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} 
    PUBLIC src/expr-token
    PUBLIC src/parser
)
