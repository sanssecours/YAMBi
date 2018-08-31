// -- Imports ------------------------------------------------------------------

#include <fstream>

#include "lexer.hpp"

using spdlog::set_level;
using spdlog::set_pattern;
using spdlog::stderr_color_mt;
using spdlog::level::trace;

using yy::parser;

using location_type = parser::location_type;
using token = parser::token;

// -- Class --------------------------------------------------------------------

/**
 * @brief This method adds the token for the start of the YAML stream to
 *        `tokens`.
 */
void Lexer::scanStart() {
  LOG("Scan start token")
  tokens.push_back(Symbol(token::TOKEN_STREAM_START, location, "STREAM START"));
}

/**
 * @brief This constructor initializes a lexer with the given input.
 *
 * @param stream This stream specifies the text which this lexer analyzes.
 */
Lexer::Lexer(ifstream &stream) : input{stream} {
  set_pattern("[%H:%M:%S:%e] %v ");
  set_level(trace);
  console = stderr_color_mt("console");
  LOG("Init lexer");

  scanStart();
}

/**
 * @brief This method returns the next token the lexer produced from `input`.
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
