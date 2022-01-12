#pragma once

#include "Node.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <iostream>
#include <unordered_set>

namespace UML {
using TypeTable = std::unordered_set<std::string>;

class UMLData {
  Node *m_node;
  TypeTable m_typeTable;

public:
  UMLData(Node *node, TypeTable typeTable)
      : m_node(node), m_typeTable(typeTable) {}
  // needs non-trivial dtor
  ~UMLData() { delete m_node; }
  TypeTable &getTypeTable() { return m_typeTable; }
  Node *getNode() const { return m_node; }
};
} // namespace UML
