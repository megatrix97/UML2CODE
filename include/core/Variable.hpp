#pragma once

#include "Attribute.hpp"

namespace UML {
class Variable : public Attribute {
 public:
  Variable(std::string type, std::string id, ACCESS access) {
    m_type = type;
    m_id = id;
    m_accessType = AccessType::getInstance(access);
  }
  Variable(std::string type, std::string id)
      : Variable(type, id, ACCESS::PRIVATE) {}
  ~Variable() = default;
  InvolvedTypes getInvolvedTypes() override;
  static bool isa(Node *node);
  void accept(NodeVisitor *visitor) override;
};
}  // namespace UML