#pragma once
#include "ast.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using node_set = std::vector<const json *>;

node_set execute(const ast::path &path, const json &root);