#ifndef LEXER_HPP
#define LEXER_HPP

#include "parser.hpp"

using std::ifstream;
using std::u32string;

using yy::parser;

class Lexer {
  u32string input;

public:
  Lexer();
  Lexer(ifstream &stream);
  virtual ~Lexer();

  parser::symbol_type nextToken();
};

#endif // LEXER_HPP
