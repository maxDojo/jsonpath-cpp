#include "ast.hpp"
#include "execute.hpp"
#include "parse.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using nlohmann::json;
int main() {
  json data = R"(
    {
      "store": {
        "book": [
          { "title": "A", "price": 8 },
          { "title": "B", "price": 12 }
        ]
      }
    }
    )"_json;

  // auto ast = parse_jsonpath("$[\"store\"][\"book\"][0].title");
  // auto ast = parse_jsonpath("$.store.book[*]");
  auto ast = parse_jsonpath("$.store['book']");
  // auto ast = parse_jsonpath("$.store.book[?(@.price < 10)].title");
  auto results = execute(ast, data);

  for (auto *j : results)
    spdlog::info("Result: {}", j->dump());

  spdlog::info("Number of ast nodes: {}\n", ast.steps.size());
}
