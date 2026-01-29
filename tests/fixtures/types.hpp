#pragma once
#include <string>

namespace test {
struct CompareResultTestCase {
  std::string name;
  std::string query;
  std::string expected_json;
};

struct CompareSizeTestCase {
  std::string name;
  std::string query;
  int expected_size;
};
} // namespace test