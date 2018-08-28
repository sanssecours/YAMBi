#ifndef LEXER_HPP
#define LEXER_HPP

#include "parser.hpp"

using yy::parser;

class Lexer {
public:
  Lexer();
  virtual ~Lexer();

  parser::symbol_type nextToken();
};

#endif // LEXER_HPP
