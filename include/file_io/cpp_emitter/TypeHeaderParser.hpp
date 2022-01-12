#ifndef __TYPEHEADERPARSER_HPP__

#define __TYPEHEADERPARSER_HPP__
#include <iostream>
#include <string>
#include <unordered_map>

struct HeaderInfo {
  std::string m_headerfile;
  std::string m_namespace;
};

using TypeHeaderInfo = std::unordered_map<std::string, HeaderInfo>;

class TypeHeaderParser {
  static TypeHeaderInfo typeHeaderInfo;
  static const std::string filename;
  static bool parsed;

public:
  static TypeHeaderInfo &parseAndGetInfo();
};

#endif