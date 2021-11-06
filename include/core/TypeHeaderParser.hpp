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
  TypeHeaderInfo m_typeHeaderInfo;
  std::string m_filename;

public:
  TypeHeaderParser(std::string filename) : m_filename(filename) {}
  void parse();
  TypeHeaderInfo getParsedInfo() { return m_typeHeaderInfo; }
};

#endif