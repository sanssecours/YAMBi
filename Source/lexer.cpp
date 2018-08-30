// -- Imports ------------------------------------------------------------------

#include <fstream>

#include "lexer.hpp"

using yy::parser;

using location_type = parser::location_type;
using token = parser::token;

// -- Class --------------------------------------------------------------------

/**
 * @brief This method adds the token for the start of the YAML stream to
 *        `tokens`.
 */
void Lexer::scanStart() {
  tokens.push_back(Symbol(token::TOKEN_STREAM_START, location, "STREAM START"));
}

/**
 * This constructor creates an empty lexer.
 */
Lexer::Lexer() {}

/**
 * This constructor initializes a lexer with the given input.
 *
 * @param stream This stream specifies the text which this lexer analyzes.
 */
Lexer::Lexer(ifstream &stream) : input{stream} { scanStart(); }

/**
 * This destructor deletes the Lexer and its instance variables.
 */
Lexer::~Lexer() {}

/**
 * This method returns the next token the lexer produced from `input`.
 *
 * @return The next token the parser has not emitted yet
 */
parser::symbol_type Lexer::nextToken() {
  if (tokens.size() < 1) {
    return parser::make_END(location);
  }

  Symbol next = tokens.front();
  tokens.pop_front();
  return next.get();
}
