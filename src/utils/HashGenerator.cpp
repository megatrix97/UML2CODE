#include "utils/HashGenerator.hpp"

namespace IRUtils {
HashKey generateHash(UML::ClassDecl* p_classDecl) {
  return p_classDecl->getId();
}
}