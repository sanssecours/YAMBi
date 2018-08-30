#ifndef SYMBOL_HPP
#define SYMBOL_HPP

// -- Imports ------------------------------------------------------------------

#include "parser.hpp"

using std::string;

using yy::parser;

using location_type = parser::location_type;
using symbol_type = parser::symbol_type;
using token_type = parser::token_type;
using token = parser::token;

// -- Class --------------------------------------------------------------------

/**
 * This class acts as wrapper for `symbol_type`, which we can not use inside a
 * queue, since its copy assignment operator is private.
 */
class Symbol {
  /** This variable stores the location of this symbol. */
  location_type placement;

  /** This variable specifies the token type of this symbol. */
  token_type tokenType;

  /** This variable stores the actual value of the symbol. */
  string text;

public:
  /**
   * @brief This constructor creates a symbol from the given arguments.
   *
   * @param type This argument specifies the token type of the symbol.
   * @param location This argument specifies the location of the symbol.
   * @param value This variable stores the value of this symbol.
   */
  Symbol(token_type const &type, location_type const &location,
         string const &value)
      : placement{location}, tokenType{type}, text{value} {}

  /**
   * @brief This method returns the Bison symbol represented by this object.
   *
   * @return A symbol representing this object
   */
  symbol_type get() {
    switch (tokenType) {
    case token::TOKEN_END:
      return parser::make_END(placement);
    case token::TOKEN_STREAM_START:
      return parser::make_STREAM_START(text, placement);
    case token::TOKEN_SCALAR:
      return parser::make_SCALAR(text, placement);
    }
  }
};

#endif // SYMBOL_HPP
