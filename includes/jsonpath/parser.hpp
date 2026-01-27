#pragma once
#include "ast.hpp"
#include <boost/spirit/home/x3.hpp>

namespace parser {
namespace x3 = boost::spirit::x3;

using path_type = x3::rule<class path, ast::path>;
using root_type = x3::rule<class root, ast::root>;
using wildcard_type = x3::rule<struct wildcard, ast::wildcard>;
using property_type = x3::rule<class property, ast::property>;
using index_type = x3::rule<class index, ast::index>;

BOOST_SPIRIT_DECLARE(path_type, root_type, wildcard_type, property_type,
                     index_type);
} // namespace parser

// expose parser function
parser::path_type path();