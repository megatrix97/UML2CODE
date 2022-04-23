#pragma once
#include <string>

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
  std::string m_destinationDir;

 public:
  const LANG getLanguage() const;
  FormatPref* setLanguage(LANG aLanguage);
  const INDENTATION getIndentation() const;
  FormatPref* setIndentation(INDENTATION aIndentation);
  const std::string getDestinationDir();
  FormatPref* setDestinationDir(std::string aDirectory);
};
}  // namespace UML