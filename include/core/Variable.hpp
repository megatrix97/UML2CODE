#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include "Attribute.hpp"

namespace UML {
class Variable : public Attribute {
 public:
  Variable(std::string type, std::string id) {
    m_type = type;
    m_id = id;
  }
  ~Variable() = default;
  InvolvedTypes getInvolvedTypes() override;
  static bool isa(Node *node);
  void accept(NodeVisitor *visitor) override;
};
}  // namespace UML

#endif