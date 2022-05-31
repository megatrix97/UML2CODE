#pragma once
#include <iostream>
#include "core/ClassDecl.hpp"

namespace IRUtils {
using HashKey = std::string;
HashKey generateHash(UML::ClassDecl *p_classDecl);
}