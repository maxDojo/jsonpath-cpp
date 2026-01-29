#include "evaluate.hpp"
#include "parse.hpp"

json evaluate(const std::string &query, const json &data) {
  auto path = parse_jsonpath(query);
  auto result_nodes = execute(path, data);
  json result_json = json::array();

  for (const auto &node : result_nodes)
    result_json.push_back(*node);

  return result_json;
}