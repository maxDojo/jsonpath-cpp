#pragma once
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

namespace ast {

struct root {};

// struct identifier {
//   std::string name;
// };

struct property {
  std::string name;
};

struct wildcard {};

struct index {
  int value;
};

struct filter;

using step =
    boost::variant<wildcard, property, index, boost::recursive_wrapper<filter>>;

struct filter {
  std::string property;
  int literal;
};

struct path {
  root root;
  std::vector<step> steps;
};

using boost::fusion::operator<<;
} // namespace ast