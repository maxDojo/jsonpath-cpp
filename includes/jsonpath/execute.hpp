#pragma once
#include "ast.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using node_set = std::vector<const json *>;

node_set execute(const ast::path &path, const json &root);

// helpers
struct normalized_arr_slice {
  int start, step, end;
};

normalized_arr_slice normalize_slice(const ast::array_slice &slice, int size);
