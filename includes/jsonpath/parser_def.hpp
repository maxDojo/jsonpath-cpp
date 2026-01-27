#pragma once
#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"
#include "ast_adapted.hpp"
#include "parser.hpp"

namespace parser {
namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using ascii::char_;

// basic parsers
auto const identifier =
    x3::lexeme[(x3::alpha | char_('_')) >> *(x3::alnum | char_('_'))];
auto const quoted_identifier =
    (x3::omit[char_('"')] >> *(char_ - char_('"')) >> x3::omit[char_('"')]) |
    (x3::omit[char_("'")] >> *(char_ - char_("'")) >> x3::omit[char_("'")]);

// root
x3::rule<struct root, ast::root> const root = "root";
auto const root_def = x3::omit[x3::lit('$')];

// selectors
x3::rule<struct wildcard, ast::wildcard> const wildcard = "wildcard";
auto const wildcard_def =
    (x3::lit('.') >> x3::omit[char_('*')]) |
    (x3::lit('[') >> x3::omit[char_('*')] >> x3::lit(']'));

x3::rule<struct property, ast::property> const property = "property";
auto const property_def =
    ('.' >> identifier) | ('[' >> quoted_identifier >> ']');

x3::rule<struct index, ast::index> const index = "index";
auto const index_def = '[' >> x3::int_ >> ']';

x3::rule<struct path, ast::path> const path = "path";
auto const path_def = root >> *(property | index | wildcard);

BOOST_SPIRIT_DEFINE(path, root, property, index, wildcard);
} // namespace parser

parser::path_type path() { return parser::path; }
