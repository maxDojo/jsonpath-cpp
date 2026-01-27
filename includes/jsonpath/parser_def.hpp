#pragma once
#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"
#include "ast_adapted.hpp"
#include "parser.hpp"

namespace parser {
namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using ascii::char_;
using x3::omit;
using x3::rule;

// basic parsers
auto const identifier =
    x3::lexeme[(x3::alpha | char_('_')) >> *(x3::alnum | char_('_'))];
auto const quoted_identifier =
    (omit[char_('"')] >> *(char_ - char_('"')) >> omit[char_('"')]) |
    (omit[char_("'")] >> *(char_ - char_("'")) >> omit[char_("'")]);

// root
rule<struct root, ast::root> const root = "root";
auto const root_def = omit[x3::lit('$')];

// selectors
rule<struct wildcard, ast::wildcard> const wildcard = "wildcard";
auto const wildcard_def = (x3::lit('.') >> omit[char_('*')]) |
                          (x3::lit('[') >> omit[char_('*')] >> x3::lit(']'));

rule<struct property, ast::property> const property = "property";
auto const property_def =
    ('.' >> identifier) | ('[' >> quoted_identifier >> ']');

rule<struct index, ast::index> const index = "index";
auto const index_def = '[' >> x3::int_ >> ']';

rule<struct array_slice, ast::array_slice> const array_slice = "array_slice";
auto const array_slice_def = omit['['] >> -x3::int_ >> omit[char_(':')] >>
                             -x3::int_ >> -omit[char_(':')] >> -x3::int_ >>
                             omit[']'];

rule<struct path, ast::path> const path = "path";
auto const path_def = root >> *(property | index | wildcard | array_slice);

BOOST_SPIRIT_DEFINE(path, root, property, index, wildcard, array_slice);
} // namespace parser
