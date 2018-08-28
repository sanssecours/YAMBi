#include "lexer.hpp"

using yy::location;
using yy::parser;

Lexer::Lexer() {}
Lexer::~Lexer() {}

parser::symbol_type Lexer::nextToken() {
  location location;
  return parser::make_END(location);
}
