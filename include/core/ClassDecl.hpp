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

/**
 * @brief ClassDecl represents a complete class with its contents.
 * @param m_attributes contain class attributes(variables and methods).
 * @param m_id contain the name of the class.
 * @param m_inherits contain reference to all the parent classes.
 */
class ClassDecl : public Node {
  AttributeList m_attributes;
  std::string m_id;
  std::vector<ClassDecl *> m_inherits;

public:
  ClassDecl(std::string id, AttributeList attributes)
      : m_id(id), m_attributes(attributes) {
    for (auto attr : attributes) {
      if (auto method = dynamic_cast<Method *>(attr)) {
        method->setClass(this);
      }
    }
  }
  ~ClassDecl() {
    // needs non-trivial destructor
    for (auto attr : m_attributes)
      delete attr;
    for (auto cls : m_inherits)
      delete cls;
  }

  const AttributeList &getAttributeList() const;

  void addAttribute(Attribute *p_attribute);

  /// @brief get number of class attributes
  const inline size_t getNumOfAttributes() const;

  const std::string &getId() const;

  /// @brief returns true if the class inherits from other class
  bool doesInherit() const;

  const std::vector<ClassDecl *> &getListOfParents() const;

  /// @brief utility function to get all the types involved in the class.
  /// Generally used to determine the required headers
  std::unordered_set<std::string> getTypesInvolved() const;

  void accept(NodeVisitor *visitor) override;
};
} // namespace UML

#endif //__CLASSDECL_HPP__