#pragma once
#include "ast.hpp"
#include "parser_def.hpp"
#include <spdlog/spdlog.h>

/** @brief Main parse function

Parses input text and returns an ast representation
*/
inline ast::path parse_jsonpath(const std::string &input) {
  using boost::spirit::x3::phrase_parse;
  using boost::spirit::x3::space;

  spdlog::info("INPUT: {}\n", input);

  ast::path result;
  auto it = input.begin();

  bool ok = phrase_parse(it, input.end(), parser::path, space, result);

  // NB: eventually add support for no-except config
  if (!ok || it != input.end())
    throw std::runtime_error("JSONPath parse error");

  return result;
}
