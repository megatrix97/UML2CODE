#pragma once
#include <iostream>
#include <unordered_map>
#include "HashGenerator.hpp"

namespace UML {
using RelationshipData = std::pair<RELATION, ClassDecl *>;
class RelationshipDataProvider {
  // <child, <relation, parent>> is the pattern relation is saved.
  static std::unordered_map<IRUtils::HashKey, RelationshipData>
      m_relationshipData;

 public:
  RelationshipDataProvider() = delete;
  static const RelationshipData *getRelationshipData(ClassDecl *p_classDecl);
  static void setRelationshipData(ClassDecl *p_parent, ClassDecl *p_child,
                                  RELATION p_relation);
  static void printContents();
};
using RDP = RelationshipDataProvider;
}