#ifndef __EMITTERTOOLS_HPP__
#define __EMITTERTOOLS_HPP__

#include <ctype.h>
#include <iostream>

namespace EmitterTools {
inline std::string firstLetterToUpper(std::string s) {
  if (!s.empty())
    s[0] = toupper(s[0]);
  return s;
}
} // namespace EmitterTools

#endif