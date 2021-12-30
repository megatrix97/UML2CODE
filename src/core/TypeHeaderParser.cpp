#include "core/TypeHeaderParser.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <stdlib.h>

void TypeHeaderParser::parse() {
  std::ifstream fileToParse;
  fileToParse.open(m_filename);
  if (!fileToParse) {
    std::cerr << "\'" << m_filename << "\'"
              << " file could not be opened" << std::endl;
    exit(1);
  }
  constexpr char patternString[] =
      R"(([a-zA-Z0-9_]+)\s*\{\s*namespace\s*:\s*([a-zA-Z0-9_]*)\s*,\s*header\s*:\s*([a-zA-Z0-9_]+)\s*\})";
  std::regex pattern(patternString);
  std::smatch matches;
  std::string line, type, nmspc;
  while (std::getline(fileToParse, line)) {
    if (std::regex_search(line, matches, pattern)) {
      type = matches.str(1);
      HeaderInfo hInfo;
      hInfo.m_headerfile = matches.str(3);
      hInfo.m_namespace = matches.str(2);
      m_typeHeaderInfo.insert(std::make_pair(type, hInfo));
    }
  }
  fileToParse.close();
}