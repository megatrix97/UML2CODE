#include "core/PrintVisitor.hpp"
#include "core/ClassDecl.hpp"
#include "core/Method.hpp"
#include "core/Variable.hpp"

namespace UML {
void PrintVisitor::visit(Node *node) { node->accept(this); }
void PrintVisitor::visit(ClassDecl *classdecl) {
  std::string format = R"({ "class" : {
    "name" : "%s",
    "attributes" : {
  )";
  char formattedStr[2048];
  sprintf(formattedStr, format.c_str(), classdecl->getId().c_str());

  std::cout << formattedStr;

  auto attributes = classdecl->getAttributeList();

  std::vector<int> variables, methods;
  int v_delim = 0, m_delim = 0;
  for (int i = 0; i < attributes.size(); i++) {
    if (Method::isa(attributes[i])) {
      methods.push_back(i);
    } else {
      variables.push_back(i);
    }
  }

  std::cout << "\"methods\" : [";
  for (int i = 0; i < methods.size(); i++) {
    std::cout << "{";
    attributes[methods[i]]->accept(this);
    std::cout << "}";
    if (m_delim < methods.size() - 1) {
      std::cout << ", ";
      m_delim++;
    }
  }

  std::cout << "], \"variables\" : [";
  for (int i = 0; i < variables.size(); i++) {
    std::cout << "{";
    attributes[variables[i]]->accept(this);
    std::cout << "}";
    if (v_delim < variables.size() - 1) {
      std::cout << ", ";
      v_delim++;
    }
  }
  std::cout << "]";

  std::cout << "}}}" << std::endl;
}
void PrintVisitor::visit(Method *method) {
  std::string format = R"("method" : { 
    "name" : "%s", 
    "returntype" : "%s", 
    "inputargs" : [)";

  char formattedStr[2048];
  sprintf(formattedStr, format.c_str(), method->getId().c_str(),
          method->getType().c_str());
  std::cout << formattedStr;

  auto inputArgs = method->getInputArgList();
  for (int i = 0; i < inputArgs.size(); i++) {
    std::cout << "{";
    inputArgs[i]->accept(this);
    std::cout << "}";

    if (i < inputArgs.size() - 1) {
      std::cout << ", ";
    }
  }

  std::cout << "]}" << std::endl;
}

void PrintVisitor::visit(Variable *variable) {
  std::string format = R"("variable" : { 
    "name" : "%s",
    "type" : "%s"
    })";

  char formattedStr[2048];
  sprintf(formattedStr, format.c_str(), variable->getId().c_str(),
          variable->getType().c_str());
  std::cout << formattedStr;
}
}  // namespace UML