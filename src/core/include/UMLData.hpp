#ifndef __UMLDATA_HPP__
#define __UMLDATA_HPP__

#include <iostream>
#include <unordered_map>

namespace UML {
class Node;

using TypeHeaderTable = std::unordered_map<std::string, std::string>;

class UMLData {
  Node *m_node;
  TypeHeaderTable m_typeHeaderTable;

public:
  UMLData(Node *node, TypeHeaderTable typeHeaderTable)
      : m_node(node), m_typeHeaderTable(typeHeaderTable) {}
  TypeHeaderTable &getTypeHeaderTable() { return m_typeHeaderTable; }
  Node *getNode() const { return m_node; }
};
} // namespace UML

#endif