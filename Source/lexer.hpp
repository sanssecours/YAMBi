#ifndef LEXER_HPP
#define LEXER_HPP

#include <deque>

#include "parser.hpp"
#include "symbol.hpp"

using std::deque;
using std::ifstream;
using std::u32string;

using symbol_type = yy::parser::symbol_type;
using location_type = yy::parser::location_type;

class Lexer {
  u32string input;
  size_t position;
  location_type location;

  /** This queue stores the list of tokens produced by the lexer. */
  // Unfortunately it is not possible to store `symbol_type` in a double ended
  // queue, since the copy assignment operator of the type is private.
  deque<Symbol> tokens;

  size_t lookahead(size_t offset);
  void consume();

  void scanStart();

public:
  Lexer();
  Lexer(ifstream &stream);
  virtual ~Lexer();

  parser::symbol_type nextToken();
};

#endif // LEXER_HPP
