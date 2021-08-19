#ifndef __CLASSDECL_HPP__
#define __CLASSDECL_HPP__

#include "Method.hpp"
#include "Node.hpp"
#include "Variable.hpp"
#include <iostream>
#include <unordered_set>
#include <vector>

namespace UML {
class Attribute;
using AttributeList = std::vector<Attribute *>;
class ClassDecl : public Node {
  AttributeList m_attributes;
  std::string m_id;
  std::vector<std::string> m_inherits;

public:
  ClassDecl(std::string id, AttributeList attributes)
      : m_id(id), m_attributes(attributes) {
    for (auto attr : attributes) {
      if (auto method = dynamic_cast<Method *>(attr)) {
        method->setClass(this);
      }
    }
  }
  const AttributeList getAttributeList() const;
  const inline size_t getNumOfAttributes() const;
  const std::string &getId() const;
  bool doesInherit() const;
  const std::vector<std::string> &getListOfParents() const;
  std::unordered_set<std::string> getTypesInvolved() const;
  void accept(NodeVisitor *visitor) override;
};
} // namespace UML

#endif //__CLASSDECL_HPP__