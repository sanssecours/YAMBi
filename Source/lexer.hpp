#ifndef LEXER_HPP
#define LEXER_HPP

// -- Imports ------------------------------------------------------------------

#include <deque>
#include <fstream>

#include "input.hpp"
#include "parser.hpp"
#include "symbol.hpp"

using std::deque;
using std::ifstream;

using symbol_type = yy::parser::symbol_type;
using location_type = yy::parser::location_type;

// -- Class --------------------------------------------------------------------

class Lexer {
  /** This attribute represents the input the lexer tokenizes. */
  Input input;

  /** This variable stores the current line and column number in Bison’s
      location format. */
  location_type location;

  /** This queue stores the list of tokens produced by the lexer. */
  deque<Symbol> tokens;

  /**
   * This method add a token stream start symbol to the token queue.
   */
  void scanStart();

public:
  /**
   * This constructor initializes a lexer with the given input.
   *
   * @param stream This stream specifies the text which this lexer analyzes.
   */
  Lexer(ifstream &stream);

  /**
   * This method returns the next token the lexer produced from `input`.
   *
   * @return The next token the parser has not emitted yet
   */
  symbol_type nextToken();
};

#endif // LEXER_HPP
