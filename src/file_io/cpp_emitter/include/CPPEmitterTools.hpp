#ifndef __CPPEMITTERTOOLS_HPP__
#define __CPPEMITTERTOOLS_HPP__

#include <iostream>

namespace UML {
namespace CPPEmitterTools {
inline std::string getVarName(std::string str) { return "m_" + str; }

inline std::string startHeaderGuard(std::string str) {
  return "#ifndef __" + str + "_HPP__\n" + "#define __" + str + "_HPP__\n";
}

inline std::string endHeaderGuard(std::string commentStr) {
  return "#endif " + (!commentStr.empty() ? "// " + commentStr : "");
}

} // namespace CPPEmitterTools
} // namespace UML

#endif