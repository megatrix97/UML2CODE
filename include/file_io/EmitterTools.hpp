#ifndef __EMITTERTOOLS_HPP__
#define __EMITTERTOOLS_HPP__

#include <ctype.h>
#include <iostream>
#include <sstream>

namespace EmitterTools {
inline std::string firstLetterToUpper(std::string s) {
  if (!s.empty())
    s[0] = toupper(s[0]);
  return s;
}
template <typename T, typename Lambda>
std::string join(T store, std::string const &sep, Lambda func = nullptr) {
  std::stringstream ss;
  auto begin = store.begin();
  auto end = store.end();
  if (begin != end) {
    if (func)
      ss << func(*begin++);
    else
      ss << *begin++;
  }
  while (begin != end) {
    if (func)
      ss << sep << func(*begin++);
    else
      ss << sep << *begin++;
  }
  return ss.str();
}
} // namespace EmitterTools

#endif