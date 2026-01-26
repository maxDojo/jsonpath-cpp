#pragma once
#include "ast.hpp"
#include <boost/spirit/home/x3.hpp>

namespace parser {
namespace x3 = boost::spirit::x3;

using x3::rule;

using path_type = rule<class path, ast::path>;
using root_type = rule<class root, ast::root>;
using property_type = rule<class property, ast::property>;
// using identifier_type = rule<class identifier, ast::property>;
using index_type = rule<class index, ast::index>;
// extern path_type const path;

BOOST_SPIRIT_DECLARE(path_type, root_type, property_type, index_type);
} // namespace parser

// expose parser function
parser::path_type path();
// parser::root_type root();
// parser::property_type property();
// // parser::identifier_type identifier();
// parser::index_type index();