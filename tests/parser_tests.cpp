// #include "catch.hpp"
#include "execute.hpp"
#include "parse.hpp"
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

using nlohmann::json;

TEST_CASE("JSONPath root", "[parser]") {
  auto path = parse_jsonpath("$.store.book[0].title");

  json data = R"({
      "store": { "book": [ { "title": "A" }, { "title": "B" } ] }
    })"_json;

  auto result = execute(path, data);

  REQUIRE(result.size() == 1);
  REQUIRE(*result[0] == "A");
}

TEST_CASE("NAME Selector", "[parser]") {
  auto path = parse_jsonpath("$.store['book'][1].title");
  json data = R"({
  "store": {"book": [{"title": "A"}, {"title": "B"}]}
  })"_json;
  auto result = execute(path, data);

  REQUIRE(result.size() == 1);
  REQUIRE(*result[0] == "B");
}

TEST_CASE("INDEX Selector", "[parser]") {
  auto path = parse_jsonpath("$.store['book'][1].title");
  json data = R"({
  "store": {"book": [{"title": "A"}, {"title": "B"}]}
  })"_json;
  auto result = execute(path, data);

  REQUIRE(result.size() == 1);
  REQUIRE(*result[0] == "B");
}

TEST_CASE("WILDCARD Selector", "[parser]") {
  auto path = parse_jsonpath("$.store.book[*].title");

  json data = R"({
      "store": { "book": [ { "title": "A" }, { "title": "B" } ] }
    })"_json;

  auto result = execute(path, data);

  REQUIRE(result.size() == 2);
  REQUIRE((*result[0] == "A" || *result[1] == "B"));
}

TEST_CASE("ARRAY_SLICE Selector", "[parser]") {
  auto path = parse_jsonpath("$.store.book[:]");
  auto path2 = parse_jsonpath("$.store.book[0:1]");

  json data = R"({
      "store": { "book": [ { "title": "A" }, { "title": "B" }, {"title": "C"}, {"title": "D"} ] }
    })"_json;

  auto result = execute(path, data);
  auto result2 = execute(path2, data);

  REQUIRE(result.size() == 4);
  REQUIRE((*result[0] == "A" || *result[1] == "B"));
}
