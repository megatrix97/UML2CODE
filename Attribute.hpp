#ifndef __ATTRIBUTE_HPP__
#define __ATTRIBUTE_HPP__

#include "Node.hpp"
#include <iostream>

namespace UML {

/**
 * @brief Class Attribute is an interface. 'void accept(NodeVisitor*)' should be
 * implemented in child classes
 *
 */

class Attribute : public Node {
protected:
  std::string m_type;
  std::string m_id;

public:
  const std::string &getId() const { return m_id; }
  const std::string &getType() const { return m_type; }
};
} // namespace UML

#endif