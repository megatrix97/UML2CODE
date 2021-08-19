#ifndef __METHOD_HPP__
#define __METHOD_HPP__

#include "Attribute.hpp"
#include "NodeVisitor.hpp"
#include "Variable.hpp"
#include <vector>

namespace UML {
class ClassDecl;
using VarList = std::vector<Variable *>;
class Method : public Attribute {
  VarList m_inputArgs;
  ClassDecl *m_class = nullptr;

public:
  Method(std::string type, std::string id, VarList inputArgs) {
    m_type = type;
    m_id = id;
    m_inputArgs = inputArgs;
    m_access = ACCESS::PRIVATE;
  }
  Method(std::string type, std::string id, VarList inputArgs,
         ACCESS accessType) {
    m_type = type;
    m_id = id;
    m_inputArgs = inputArgs;
    m_access = accessType;
  }
  const VarList &getInputArgList() const { return m_inputArgs; }
  const inline size_t getNumOfInputArgs() const { return m_inputArgs.size(); }
  bool isPropertyOfClass() const { return m_class != nullptr; }
  ClassDecl *getClass() const { return m_class; }
  void setClass(ClassDecl *classDecl) { m_class = classDecl; }
  static bool isa(Node *node);
  void accept(NodeVisitor *visitor) override;
};
} // namespace UML

#endif