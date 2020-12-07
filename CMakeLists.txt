cmake_minimum_required(VERSION 3.5)
project(SysY-Compiler VERSION "0.0.1")

# C++17 standard support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

flex_target(SysYLexer 
    src/sysy2eeyore/sysy.l 
    ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp
)
bison_target(SysYParser 
    src/sysy2eeyore/sysy.y 
    ${CMAKE_CURRENT_BINARY_DIR}/sysy.tab.cpp
)
add_flex_bison_dependency(SysYLexer SysYParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(src)
include_directories(src/sysy2eeyore)

file(GLOB_RECURSE SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} ${FLEX_SysYLexer_OUTPUTS}
    ${BISON_SysYParser_OUTPUT_SOURCE})

add_executable(compiler
    ${SOURCES}
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Scanner_OUTPUTS}
)
