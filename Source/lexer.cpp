#include <codecvt>
#include <fstream>
#include <sstream>

#include "lexer.hpp"

using std::codecvt_utf8;
using std::stringstream;
using std::wstring_convert;

using yy::location;

Lexer::Lexer() {}
Lexer::~Lexer() {}

Lexer::Lexer(ifstream &stream) {
  stringstream stringStream;
  stringStream << stream.rdbuf();
  input = wstring_convert<codecvt_utf8<char32_t>, char32_t>{}.from_bytes(
      stringStream.str());
}

parser::symbol_type Lexer::nextToken() {
  location location;
  return parser::make_END(location);
}
