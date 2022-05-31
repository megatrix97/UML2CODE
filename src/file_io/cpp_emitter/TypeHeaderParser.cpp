#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <stdlib.h>

bool TypeHeaderParser::parsed = false;
std::string const TypeHeaderParser::filename =
    R"(C:\Users\nithi\Documents\Learning\CPP\Project\uml2code\res\CPPTypeheaders.txt)";
TypeHeaderInfo TypeHeaderParser::typeHeaderInfo{};

TypeHeaderInfo *TypeHeaderParser::parseAndGetInfo() {
  if (parsed)
    return &typeHeaderInfo;

  std::ifstream fileToParse;
  fileToParse.open(filename);
  if (!fileToParse) {
    std::cerr << "\'" << filename << "\'"
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
      typeHeaderInfo.insert(std::make_pair(type, hInfo));
    }
  }
  fileToParse.close();
  parsed = true;
  return &typeHeaderInfo;
}