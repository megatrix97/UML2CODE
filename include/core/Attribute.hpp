#pragma once

#include "Node.hpp"
#include <iostream>
#include <vector>

namespace UML {

enum ACCESS { PUBLIC, PRIVATE, PROTECTED };

using InvolvedTypes = std::vector<std::string>;

/**
 * @brief Class Attribute is an interface. 'void accept(NodeVisitor*)' should be
 * implemented in child classes
 *
 */

class Attribute : public Node {
 protected:
  std::string m_type;
  std::string m_id;
  ACCESS m_access;

 public:
  ~Attribute() = default;
  std::string getId() const { return m_id; }
  std::string getType() const { return m_type; }
  virtual InvolvedTypes getInvolvedTypes() = 0;
  const ACCESS &getAccessType() const { return m_access; }
};
}  // namespace UML