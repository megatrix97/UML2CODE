#include "core/ClassDecl.hpp"
#include "core/Attribute.hpp"
#include "core/NodeVisitor.hpp"
#include <unordered_set>

namespace UML {
const std::string &ClassDecl::getId() const { return m_id; }

const AttributeList &ClassDecl::getAttributeList() const {
  return m_attributes;
}

void ClassDecl::addAttribute(Attribute *p_attribute) {
  InvolvedTypes it = p_attribute->getInvolvedTypes();
  for (auto i : it) {
    m_typesInvolved.insert(i);
  }
  m_attributes.push_back(p_attribute);
}

const inline size_t ClassDecl::getNumOfAttributes() const {
  return m_attributes.size();
}

std::unordered_set<std::string> ClassDecl::getInvolvedTypes() const {
  return m_typesInvolved;
}

const std::vector<ClassDecl *> &ClassDecl::getClassesRelatedWith(
    RELATION p_relation) {
  if (m_relatedClasses.find(p_relation) != m_relatedClasses.end()) {
    return m_relatedClasses[p_relation];
  }
}

void ClassDecl::accept(NodeVisitor *visitor) { visitor->visit(this); }
}  // namespace UML