#pragma once

#include "Method.hpp"
#include "Node.hpp"
#include "Variable.hpp"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace UML {

enum RELATION {
  AGGREGATION,
  INHERITANCE,
  COMPOSITION,
  DEPENDENCY,
  ASSOCIATION
};

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
  std::unordered_set<std::string> m_typesInvolved;
  std::unordered_map<RELATION, std::vector<ClassDecl *>> m_relatedClasses;

 public:
  ClassDecl(std::string id) : m_id(id) {}
  ClassDecl(std::string id, AttributeList attributes)
      : m_id(id), m_attributes(attributes) {
    for (auto attr : attributes) {
      if (auto method = dynamic_cast<Method *>(attr)) {
        method->setClass(this);
      }
    }
  }

  ~ClassDecl() {
    for (auto attr : m_attributes) delete attr;
  }

  const AttributeList &getAttributeList() const;

  void addAttribute(Attribute *p_attribute);

  /// @brief get number of class attributes
  const inline size_t getNumOfAttributes() const;

  const std::string &getId() const;

  /// @brief utility function to get all the types involved in the class.
  /// Generally used to determine the required headers
  std::unordered_set<std::string> getInvolvedTypes() const;

  const std::vector<ClassDecl *> *getClassesRelatedWith(RELATION p_relation);

  void accept(NodeVisitor *visitor) override;
};
}  // namespace UML