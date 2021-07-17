#include "include/ClassDecl.hpp"
#include "include/NodeVisitor.hpp"
#include <yvals.h>

namespace UML {
const std::string &ClassDecl::getId() const { return m_id; }
const AttributeList ClassDecl::getAttributeList() const { return m_attributes; }
const inline size_t ClassDecl::getNumOfAttributes() const {
  return m_attributes.size();
}
void ClassDecl::accept(NodeVisitor *visitor) { visitor->visit(this); }
} // namespace UML