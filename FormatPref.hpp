#ifndef __FORMATCONFIG_HPP__
#define __FORMATCONFIG_HPP__

namespace UML {
enum LANG { C, CPP };
enum INDENTATION { DEFAULT, TAB };
/**
 * @brief Class FormatPref holds all the formatting preferences of the user.
 * It uses Builder design pattern. This will allow to add new options at later
 * stages easily.
 *
 */
class FormatPref {
  LANG m_language;
  INDENTATION m_indentation;

public:
  const LANG getLanguage() const;
  FormatPref setLanguage(LANG aLanguage);
  const INDENTATION getIndentation() const;
  FormatPref setIndentation(INDENTATION aIndentation);
};
} // namespace UML

#endif