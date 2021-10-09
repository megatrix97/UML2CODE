#ifndef __UMLDATA_HPP__
#define __UMLDATA_HPP__

#include "Node.hpp"
#include "TypeHeaderParser.hpp"
#include <iostream>
#include <unordered_set>


namespace UML {
using TypeTable = std::unordered_set<std::string>;

class UMLData {
  Node *m_node;
  TypeTable m_typeTable;
  TypeHeaderInfo m_typeHeaderInfo;

public:
  UMLData(Node *node, TypeTable typeTable, TypeHeaderInfo typeHeaderInfo)
      : m_node(node), m_typeTable(typeTable), m_typeHeaderInfo(typeHeaderInfo) {
  }
  // needs non-trivial dtor
  ~UMLData() { delete m_node; }
  TypeTable &getTypeTable() { return m_typeTable; }
  TypeHeaderInfo &getTypeHeaderInfo() { return m_typeHeaderInfo; }
  Node *getNode() const { return m_node; }
};
} // namespace UML

#endif