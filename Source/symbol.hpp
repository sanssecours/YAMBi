#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include "parser.hpp"

using std::string;

using yy::parser;

using location_type = parser::location_type;
using symbol_type = parser::symbol_type;
using token_type = parser::token_type;
using token = parser::token;

class Symbol {
private:
  location_type location;
  token_type token;
  string value;

public:
  Symbol(token_type const &token, location_type const &location,
         string const &value)
      : location{location}, token{token}, value{value} {}

  symbol_type get() {
    switch (token) {
    case token::TOKEN_END:
      return parser::make_END(location);
    case token::TOKEN_STREAM_START:
      return parser::make_STREAM_START(value, location);
    case token::TOKEN_SCALAR:
      return parser::make_SCALAR(value, location);
    }
  }
};

#endif // SYMBOL_HPP
