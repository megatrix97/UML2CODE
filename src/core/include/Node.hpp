#ifndef __NODE_HPP__
#define __NODE_HPP__

namespace UML {
class NodeVisitor;

class Node {
public:
  virtual void accept(NodeVisitor *aVisitor) = 0;
};
} // namespace UML

#endif // __NODE_HPP__