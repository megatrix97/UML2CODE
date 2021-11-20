#ifndef __CPPEMITTERTOOLS_HPP__
#define __CPPEMITTERTOOLS_HPP__

#include <iostream>

namespace UML {
namespace CPPEmitterTools {
inline std::string getVarName(std::string str) { return "m_" + str; }

} // namespace CPPEmitterTools
} // namespace UML

#endif