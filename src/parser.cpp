#include "config.hpp"
#include "parser_def.hpp"

namespace parser {
BOOST_SPIRIT_INSTANTIATE(path_type, iterator_type, context_type);
}