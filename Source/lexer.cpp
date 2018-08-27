#include "lexer.hpp"

using yy::location;
using yy::parser;

Lexer::Lexer() {}
Lexer::~Lexer() {}

parser::symbol_type yylex(Driver &driver __attribute__((unused))) {
  location location;
  return parser::make_END(location);
}
