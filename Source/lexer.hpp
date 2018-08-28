#ifndef LEXER_HPP
#define LEXER_HPP

#include "parser.hpp"

using std::ifstream;

using yy::parser;

class Lexer {
  ifstream *input;

public:
  Lexer();
  Lexer(ifstream &stream);
  virtual ~Lexer();

  parser::symbol_type nextToken();
};

#endif // LEXER_HPP
