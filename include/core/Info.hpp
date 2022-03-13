#pragma once

#include "ClassDecl.hpp"

namespace UML {
class Info {
  ClassDecl *m_classDecl;

 public:
  ClassDecl *getInfoElement() { return m_classDecl; }
};
}