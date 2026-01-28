FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.12.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(Catch2)

add_executable(${PARSER_TESTS}
parser_tests.cpp
executor_tests.cpp
)

target_include_directories(${PARSER_TESTS} PRIVATE ${PARSER_INCLUDES} ${Boost_INCLUDE_DIRS})

target_link_libraries(${PARSER_TESTS}
    PUBLIC
        Catch2::Catch2WithMain
        nlohmann_json::nlohmann_json
        ${PARSER_LIB}
)

include(CTest)
include(Catch)

catch_discover_tests(${PARSER_TESTS})
