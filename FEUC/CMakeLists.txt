cmake_minimum_required(VERSION 4.3.1)

set(TOOL_EXE "FEUC")

add_executable(${TOOL_EXE} "src/main.cpp" "src/FEUC.cpp")

set_target_properties(${TOOL_EXE} PROPERTIES
CXX_STANDARD 11
CXX_STANDARD_REQUIRED ON
CXX_EXTENSIONS OFF)

target_include_directories(${TOOL_EXE} PRIVATE "include/")
target_precompile_headers(${TOOL_EXE} PRIVATE "include/PCH.hpp")

add_subdirectory(src)