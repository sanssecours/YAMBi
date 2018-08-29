#ifndef LEXER_HPP
#define LEXER_HPP

// -- Imports ------------------------------------------------------------------

#include <deque>

#include "parser.hpp"
#include "symbol.hpp"

using std::deque;
using std::ifstream;
using std::u32string;

using symbol_type = yy::parser::symbol_type;
using location_type = yy::parser::location_type;

// -- Class --------------------------------------------------------------------

class Lexer {
  /** This variable stores the content of the file the lexer is currently
      parsing. */
  u32string input;

  /** This variable stores the current position inside `input`. */
  size_t position;

  /** This variable stores the current line and column number in Bison’s
      location format. */
  location_type location;

  /** This queue stores the list of tokens produced by the lexer. */
  deque<Symbol> tokens;

  /**
   * This function returns a token the lexer has not consumed yet.
   *
   * @param offset This variable specifies the index of the character
   *               this method should retrieve as offset to the last consumed
   *               character.
   *
   * @return The character which is `offset` positions away from the last
   *         consumed character
   */
  size_t lookahead(size_t offset);

  /**
   * This method consumes the next character of `input`.
   */
  void consume();

  /**
   * This method add a token stream start symbol to the token queue.
   */
  void scanStart();

public:
  /**
   * This constructor creates an empty lexer.
   */
  Lexer();

  /**
   * This constructor initializes a lexer with the given input.
   *
   * @param stream This stream specifies the text which this lexer analyzes.
   */
  Lexer(ifstream &stream);

  /**
   * This destructor deletes the Lexer and its instance variables.
   */
  virtual ~Lexer();

  /**
   * This method returns the next token the lexer produced from `input`.
   *
   * @return The next token the parser has not emitted yet
   */
  symbol_type nextToken();
};

#endif // LEXER_HPP
