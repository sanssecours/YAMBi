#ifndef LEXER_HPP
#define LEXER_HPP

#include <deque>

#include "parser.hpp"
#include "symbol.hpp"

using std::deque;
using std::ifstream;
using std::u32string;

using yy::parser;

class Lexer {
  u32string input;
  size_t position;

  /** This queue stores the list of tokens produced by the lexer. */
  // Unfortunately it is not possible to store `symbol_type` in a double ended
  // queue, since the copy assignment operator of the type is private.
  deque<Symbol> tokens;

  size_t lookahead(size_t offset);
  void consume();

public:
  Lexer();
  Lexer(ifstream &stream);
  virtual ~Lexer();

  parser::symbol_type nextToken();
};

#endif // LEXER_HPP
