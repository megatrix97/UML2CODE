#ifndef __NODEVISITOR_HPP__
#define __NODEVISITOR_HPP__

namespace UML {
class Node;
class ClassDecl;
class Variable;
class Method;

/**
 * @brief Class NodeVisitor is an interface. Any visitor child classes can
 * implement any/all of virtual methods
 *
 */

class NodeVisitor {
public:
  virtual void visit(Node *n) = 0;
  virtual void visit(ClassDecl *classdecl) = 0;
  virtual void visit(Variable *variable) = 0;
  virtual void visit(Method *method) = 0;
};
} // namespace UML

#endif // __NODEVISITOR_HPP__