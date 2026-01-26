#include "ast.hpp"
#include "ast_adapted.hpp"
#include "execute.hpp"
#include "parse.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

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

  auto ast = parse_jsonpath("$[\"store\"][\"book\"][0].title");
  // auto ast = parse_jsonpath("$.store.book[0].title");
  // auto ast = parse_jsonpath("$.store.book[?(@.price < 10)].title");
  auto results = execute(ast, data);

  for (auto *j : results)
    std::cout << "Result: " << *j << "\n";

  std::cout << "Sizeof ast steps: " << ast.steps.size() << "\n";
}
