cmake_minimum_required(VERSION 4.2)

project(jsonpath_cpp VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED)

set(EXECUTABLE Exe)
set(PARSER_LIB jsonpath)
set(PARSER_INCLUDES ${CMAKE_SOURCE_DIR}/includes/ast
                    ${CMAKE_SOURCE_DIR}/includes/jsonpath
)
set(PARSER_SOURCES  ${CMAKE_SOURCE_DIR}/src/execute.cpp
                    ${CMAKE_SOURCE_DIR}/src/parser.cpp
)

# Add external dependencies
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.17.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(spdlog)

add_executable(${EXECUTABLE} main.cpp)
target_include_directories(${EXECUTABLE} PRIVATE ${PARSER_INCLUDES} ${Boost_INCLUDE_DIRS})

# subdirectories
add_subdirectory(src)
add_subdirectory(includes)
target_link_libraries(Exe PUBLIC ${PARSER_LIB} spdlog::spdlog_header_only)
