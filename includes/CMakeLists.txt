target_include_directories(${PARSER_LIB} PRIVATE ${PARSER_INCLUDES} ${Boost_INCLUDE_DIRS})
target_link_libraries(${PARSER_LIB} PUBLIC nlohmann_json::nlohmann_json spdlog::spdlog_header_only)