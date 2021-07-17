#ifndef __METHOD_HPP__
#define __METHOD_HPP__

#include "Attribute.hpp"
#include "NodeVisitor.hpp"
#include "Variable.hpp"
#include <vector>

namespace UML {
using VarList = std::vector<Variable *>;
class Method : public Attribute {
  VarList m_inputArgs;

public:
  Method(std::string type, std::string id, VarList inputArgs) {
    m_type = type;
    m_id = id;
    m_inputArgs = inputArgs;
  }
  const VarList &getInputArgList() const { return m_inputArgs; }
  const inline size_t getNumOfInputArgs() const { return m_inputArgs.size(); }
  static bool isa(Node *node);
  void accept(NodeVisitor *visitor) override;
};
} // namespace UML

#endif