#pragma once
#include <iostream>
#include <unordered_map>
#include "HashGenerator.hpp"

namespace UML {
using RelationshipData = std::pair<RELATION, ClassDecl *>;
class RelationshipDataProvider {
  // relation is saved in <child, <relation, parent>> pattern.
  std::unordered_map<IRUtils::HashKey, RelationshipData> m_relationshipData;

 public:
  const RelationshipData *getRelationshipData(ClassDecl *p_classDecl);
  void setRelationshipData(ClassDecl *p_parent, ClassDecl *p_child,
                           RELATION p_relation);
  void printContents();
};
using RDP = RelationshipDataProvider;
}