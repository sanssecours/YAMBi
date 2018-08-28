#include "lexer.hpp"

using yy::location;

Lexer::Lexer() {}
Lexer::~Lexer() {}

Lexer::Lexer(ifstream &stream) { input = &stream; }

parser::symbol_type Lexer::nextToken() {
  location location;
  return parser::make_END(location);
}
