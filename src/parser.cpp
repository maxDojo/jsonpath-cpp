#include "config.hpp"
#include "parser_def.hpp"

parser::path_type path() { return parser::path; }
namespace parser {
BOOST_SPIRIT_INSTANTIATE(path_type, iterator_type, context_type);
}