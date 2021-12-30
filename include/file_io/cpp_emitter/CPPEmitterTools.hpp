#pragma once
#include <iostream>

namespace UML {
namespace CPPEmitterTools {
inline std::string getVarName(std::string str) { return "m_" + str; }

} // namespace CPPEmitterTools
} // namespace UML
