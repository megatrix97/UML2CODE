#include "../../include/core/ClassDecl.hpp"
#include "../../include/core/NodeVisitor.hpp"
#include <unordered_set>

namespace UML {
const std::string &ClassDecl::getId() const { return m_id; }

const AttributeList ClassDecl::getAttributeList() const { return m_attributes; }

const inline size_t ClassDecl::getNumOfAttributes() const {
  return m_attributes.size();
}

bool ClassDecl::doesInherit() const { return !m_inherits.empty(); }

const std::vector<ClassDecl *> &ClassDecl::getListOfParents() const {
  return m_inherits;
}

std::unordered_set<std::string> ClassDecl::getTypesInvolved() const {
  std::unordered_set<std::string> allTypes;
  for (auto attr : m_attributes) {
    allTypes.insert(attr->getType());
  }
  return allTypes;
}

void ClassDecl::accept(NodeVisitor *visitor) { visitor->visit(this); }
} // namespace UML