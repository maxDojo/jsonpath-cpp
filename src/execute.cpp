#include "execute.hpp"
#include <iostream>

struct step_executor {

  const node_set &input;
  const json &root;

  node_set operator()(const ast::root &) const { return {&root}; }

  node_set operator()(const ast::property &p) const {
    std::cout << "Property: " << p.name << "\n";
    node_set out;
    for (auto *n : input) {
      if (n->is_object() && n->contains(p.name))
        out.push_back(&(*n)[p.name]);
    }
    return out;
  }

  node_set operator()(const ast::index &i) const {
    std::cout << "Index: " << i.value << "\n";
    node_set out;
    for (auto *n : input) {
      if (n->is_array() && i.value < n->size())
        out.push_back(&(*n)[i.value]);
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
