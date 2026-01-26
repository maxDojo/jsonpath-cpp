#pragma once
#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"
#include "ast_adapted.hpp"
#include "parser.hpp"

namespace parser {
namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using ascii::char_;
using x3::lexeme;
using x3::omit;
using x3::rule;

// rule<class identifier, ast::identifier> const identifier =
//     "identifier";
auto const identifier = lexeme[x3::alpha >> *(x3::alnum | char_('_'))];
auto const quoted_identifier =
    (omit[char_('"')] >> identifier >> omit[char_('"')]) |
    (omit[char_("'")] >> identifier >> omit[char_("'")]);

rule<class root, ast::root> const root = "root";
// auto const root_def = x3::char_('$');
auto const root_def = x3::lit('$') >> x3::attr(ast::root{});

rule<class property, ast::property> const property = "property";
auto const property_def =
    ('.' >> identifier) | ('[' >> quoted_identifier >> ']');

rule<class index, ast::index> const index = "index";
auto const index_def = '[' >> x3::int_ >> ']';

rule<class path, ast::path> const path = "path";
auto const path_def = root >> *(property | index);

BOOST_SPIRIT_DEFINE(path, root, property, index);
} // namespace parser

parser::path_type path() { return parser::path; }
// parser::root_type root() { return parser::root; }
