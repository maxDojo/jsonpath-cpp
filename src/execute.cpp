#include "execute.hpp"
#include <spdlog/spdlog.h>

struct step_executor {

  const node_set &input;
  const json &root;

  node_set operator()(const ast::wildcard &) {
    spdlog::debug("Wildcard node!");

    // non-compliant behaviour, appears to output content in an array, will
    // verify eventually
    return input;
  }

  node_set operator()(const ast::property &p) const {
    spdlog::debug("Property node: {}", p.name);
    node_set out;
    for (auto *n : input) {
      if (n->is_object() && n->contains(p.name))
        out.push_back(&(*n)[p.name]);
    }
    return out;
  }

  node_set operator()(const ast::index &i) const {
    spdlog::debug("Index_node: {}", i.value);
    node_set out;
    for (auto *n : input) {
      if (n->is_array() && i.value < n->size())
        out.push_back(&(*n)[i.value]);
    }
    return out;
  }

  node_set operator()(const ast::array_slice &slice) {
    node_set out;
    int step = slice.step.value_or(1);

    for (auto *node : input) {
      if (!node->is_array()) {
        spdlog::error(
            "EXECUTING FILTER ON NON-ARRAY OBJECT {} RETURNS EMPTY ARRAY!",
            node->dump());
        continue;
      }
      if (step == 0) {
        spdlog::error("[ARRAY_SLICE] STEP VALUE CANNOT BE ZERO "
                      "[(start):(end):(step)->{}]",
                      step);
        continue;
      }

      int size = node->size(), start, end;

      if (size == 0)
        continue;

      if (step > 0) {
        if (!slice.start.has_value())
          start = 0;
        else {
          start = slice.start.value();

          if (start < 0)
            start += size;
          start = std::clamp(start, 0, size);
        }

        if (!slice.end.has_value())
          end = size;
        else {
          end = slice.end.value();

          if (end < 0)
            end += size;
          end = std::clamp(end, 0, size);
        }

        for (int i = start; i < end; i += step)
          out.push_back(&(*node)[i]);
      } else {
        if (!slice.start.has_value())
          start = size - 1;
        else {
          start = slice.start.value();

          if (start < 0)
            start += size;
          start = std::clamp(start, 0, size - 1);
        }

        if (!slice.end.has_value())
          end = -1;
        else {
          end = slice.end.value();

          if (end < 0)
            end += size;
          end = std::clamp(end, -1, size - 1);
        }

        for (int i = start; i > end; i += step)
          out.push_back(&(*node)[i]);
      }
    }

    return out;
  }

  node_set operator()(const ast::filter &f) const {
    node_set out;
    for (auto *n : input) {
      if (!n->is_array())
        continue;

      for (auto &el : *n) {
        if (el.is_object() && el.contains(f.property) &&
            el[f.property] < f.literal) {
          out.push_back(&el);
        }
      }
    }
    return out;
  }
};

node_set execute(const ast::path &path, const json &root) {
  node_set current{&root};

  for (const auto &step : path.steps) {
    current = boost::apply_visitor(step_executor{current, root}, step);
  }

  return current;
}