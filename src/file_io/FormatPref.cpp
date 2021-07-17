#include "include/FormatPref.hpp"

namespace UML {
const LANG FormatPref::getLanguage() const { return m_language; }
const INDENTATION FormatPref::getIndentation() const { return m_indentation; }
FormatPref FormatPref::setLanguage(LANG aLanguage) {
  m_language = aLanguage;
  return *this;
}
FormatPref FormatPref::setIndentation(INDENTATION aIndentation) {
  m_indentation = aIndentation;
  return *this;
}
} // namespace UML