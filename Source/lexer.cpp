// -- Imports ------------------------------------------------------------------

#include <fstream>

#include "lexer.hpp"

#if defined(__clang__)
using spdlog::set_level;
using spdlog::set_pattern;
using spdlog::stderr_color_mt;
using spdlog::level::trace;
#endif

using yy::parser;

using location_type = parser::location_type;
using token = parser::token;

// -- Class --------------------------------------------------------------------

/**
 * @brief This method consumes characters from the input stream keeping
 *        track of line and column numbers.
 *
 * @param characters This parameter specifies the number of characters the
 *                   the function should consume.
 */
void Lexer::forward(size_t const characters = 1) {
  LOGF("Forward {} characters", characters);

  for (size_t charsLeft = characters; charsLeft > 0; charsLeft--) {
    if (input.lookahead(1) == 0) {
      LOG("Hit EOF!");
      return;
    }

    location += 1;
    if (input.lookahead(1) == '\n') {
      location.end.column = 1;
      location.lines();
    }
    input.consume();
  }
}

/**
 * @brief This method adds new tokens to the token queue.
 */
void Lexer::fetchTokens() {}

/**
 * @brief This method adds the token for the start of the YAML stream to
 *        `tokens`.
 */
void Lexer::scanStart() {
  LOG("Scan start token");
  tokens.push_back(Symbol(token::TOKEN_STREAM_START, location, "STREAM START"));
}

/**
 * @brief This method adds the token for the end of the YAML stream to
 *        the token queue.
 */
void Lexer::scanEnd() {
  LOG("Scan end token");
  tokens.push_back(Symbol(token::TOKEN_STREAM_END, location, "STREAM END"));
}

/**
 * @brief This constructor initializes a lexer with the given input.
 *
 * @param stream This stream specifies the text which this lexer analyzes.
 */
Lexer::Lexer(ifstream &stream) : input{stream} {
#if defined(__clang__)
  set_pattern("[%H:%M:%S:%e] %v ");
  set_level(trace);
  console = stderr_color_mt("console");
#endif
  LOG("Init lexer");

  scanStart();
  fetchTokens();
  scanEnd();
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
