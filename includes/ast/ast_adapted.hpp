#pragma once
#include "ast.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(ast::property, name)
BOOST_FUSION_ADAPT_STRUCT(ast::index, value)
BOOST_FUSION_ADAPT_STRUCT(ast::filter, property, literal)
BOOST_FUSION_ADAPT_STRUCT(ast::path, root, steps)
BOOST_FUSION_ADAPT_STRUCT(ast::array_slice, start, end, step)