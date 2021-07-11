#include "Variable.hpp"
#include "NodeVisitor.hpp"

namespace UML {
void Variable::accept(NodeVisitor *visitor) { visitor->visit(this); }
} // namespace UML