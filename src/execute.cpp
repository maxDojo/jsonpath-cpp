#include "execute.hpp"
#include "ast.hpp"
#include <spdlog/spdlog.h>
#include <stdexcept>

struct step_executor {

  const node_set &input;
  const json &root;

  node_set operator()(const ast::wildcard &) {
    spdlog::info("Wildcard node!");

    // non-compliant behaviour, appears to output content in an array, will
    // verify eventually
    return input;
  }

  node_set operator()(const ast::property &p) const {
    spdlog::info("Property node: {}", p.name);
    node_set out;
    for (auto *n : input) {
      if (n->is_object() && n->contains(p.name))
        out.push_back(&(*n)[p.name]);
    }
    return out;
  }

  node_set operator()(const ast::index &i) const {
    spdlog::info("Index_node: {}", i.value);
    node_set out;
    for (auto *n : input) {
      if (n->is_array() && i.value < n->size())
        out.push_back(&(*n)[i.value]);
    }
    return out;
  }

  node_set operator()(const ast::array_slice &slice) {
    node_set out;

    for (auto *n : input) {
      // check if json input is array, skip otherwise
      if (!n->is_array()) {
        spdlog::error(
            "Executing filter on non-array object {} returns empty array!",
            n->dump());
        continue;
      }

      const int size = static_cast<int>(input.size());
      auto n_slice = normalize_slice(slice, size);

      spdlog::info("Array slice node start: {}, end: {}, step: {}.",
                   n_slice.start, n_slice.end, n_slice.step);

      if (n_slice.step > 0) {
        for (int i = n_slice.start; i < n_slice.end; i += n_slice.step) {
          if (i >= 0 && i < size)
            out.push_back(input[i]);
        }
      } else {
        for (int i = n_slice.start; i > n_slice.end; i += n_slice.step) {
          if (i >= 0 && i < size)
            out.push_back(input[i]);
        }
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

normalized_arr_slice normalize_slice(const ast::array_slice &slice, int size) {
  int step = slice.step.value_or(1);
  if (step == 0)
    throw std::runtime_error("array slice step cannot be zero");

  int start;
  int end;

  if (step > 0) {
    start = slice.start.value_or(0);
    end = slice.end.value_or(size);
  } else {
    start = slice.start.value_or(size - 1);
    end = slice.end.value_or(-1);
  }

  if (start < 0)
    start += size;
  if (end < 0)
    end += size;

  start = std::clamp(start, 0, size);
  end = std::clamp(end, -1, size);

  return {start, end, step};
};