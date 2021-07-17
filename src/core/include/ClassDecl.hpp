#ifndef __CLASSDECL_HPP__
#define __CLASSDECL_HPP__

#include "Node.hpp"
#include "Variable.hpp"
#include <iostream>
#include <vector>

namespace UML {
class Attribute;
using AttributeList = std::vector<Attribute *>;
class ClassDecl : public Node {
  AttributeList m_attributes;
  std::string m_id;

public:
  ClassDecl(std::string id, AttributeList attributes)
      : m_id(id), m_attributes(attributes) {}
  const AttributeList getAttributeList() const;
  const inline size_t getNumOfAttributes() const;
  const std::string &getId() const;
  void accept(NodeVisitor *visitor) override;
};
} // namespace UML

#endif //__CLASSDECL_HPP__