#include "evaluate.hpp"
#include "fixtures/sample_json.hpp"
#include "fixtures/types.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("JSONPath array slicing returns correct elements",
          "[array_slice][selectors]") {
  const auto json_data = &test::data;

  const test::CompareResultTestCase cases[] = {
      {"start:end within limits", "$.store.books[1:3]",
       R"(
      [{
        "category": "fiction",
        "author": "Evelyn Waugh",
        "title": "Sword of Honour",
        "price": 12.99,
        "available": false,
        "tags": []
      },
      {
        "category": "fiction",
        "author": "Herman Melville",
        "title": "Moby Dick",
        "price": 8.99,
        "isbn": "0-553-21311-4",
        "available": true,
        "tags": ["classic", "whale"]
  }])"},
      {"reverse slice", "$.store.books[::-1]",
       R"([
      {
        "category": "fiction",
        "author": "Herman Melville",
        "title": "Moby Dick",
        "price": 8.99,
        "isbn": "0-553-21311-4",
        "available": true,
        "tags": ["classic", "whale"]
      },
      {
        "category": "fiction",
        "author": "Evelyn Waugh",
        "title": "Sword of Honour",
        "price": 12.99,
        "available": false,
        "tags": []
      },
      {
        "category": "reference",
        "author": "Nigel Rees",
        "title": "Sayings of the Century",
        "price": 8.95,
        "isbn": "0-553-21311-3",
        "available": true,
        "tags": ["quotes", "history"]
      }])"}};

  for (const auto &c : cases) {
    SECTION(c.name) {
      auto result = evaluate(c.query, *json_data);
      auto expected = json::parse(c.expected_json);

      REQUIRE(result == expected);
    }
  }
}