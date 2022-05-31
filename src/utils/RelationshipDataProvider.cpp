#include "utils/RelationshipDataProvider.hpp"

namespace UML {
const RelationshipData* RDP::getRelationshipData(ClassDecl* p_classDecl) {
  IRUtils::HashKey hash = IRUtils::generateHash(p_classDecl);
  return m_relationshipData.find(hash) != m_relationshipData.end()
             ? &m_relationshipData[hash]
             : nullptr;
}

void RDP::setRelationshipData(ClassDecl* p_parent, ClassDecl* p_child,
                              RELATION p_relation) {
  m_relationshipData.insert(std::make_pair(
      IRUtils::generateHash(p_child), std::make_pair(p_relation, p_parent)));
}

void RDP::printContents() {
  char output[2048];
  std::string format = R"({ relation : {
    type : "%d",
    parent : "%s",
    child : "%s" 
  }})";

  for (auto& content : m_relationshipData) {
    sprintf(output, format.c_str(), content.second.first,
            content.second.second->getId().c_str(), content.first.c_str());
    std::cout << output << std::endl;
  }
}
}