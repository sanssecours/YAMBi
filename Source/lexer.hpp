#ifndef LEXER_HPP
#define LEXER_HPP

#include "parser.hpp"

using yy::parser;

class Lexer {
  Lexer();
  virtual ~Lexer();

  parser::symbol_type yylex(Driver &driver);
};

#endif // LEXER_HPP
