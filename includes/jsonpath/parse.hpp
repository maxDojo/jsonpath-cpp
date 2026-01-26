#pragma once
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "parser_def.hpp"
#include <iostream>

inline ast::path parse_jsonpath(const std::string &input) {
  using boost::spirit::x3::phrase_parse;
  using boost::spirit::x3::space;

  std::cout << "INPUT: " << input << "\n\n";

  ast::path result;
  auto it = input.begin();

  bool ok = phrase_parse(it, input.end(), parser::path, space, result);

  if (!ok || it != input.end())
    throw std::runtime_error("JSONPath parse error");

  return result;
}
