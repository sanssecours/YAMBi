#ifndef LEXER_HPP
#define LEXER_HPP

// -- Macros -------------------------------------------------------------------

#define SPDLOG_TRACE_ON
#define LOGF(fmt, ...)                                                         \
  console->trace("{}:{}: " fmt, __FUNCTION__, __LINE__, __VA_ARGS__);
#define LOG(text) console->trace("{}:{}: {}", __FUNCTION__, __LINE__, text);

// -- Imports ------------------------------------------------------------------

#include <deque>
#include <fstream>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "input.hpp"
#include "parser.hpp"
#include "symbol.hpp"

using spdlog::logger;

using std::deque;
using std::ifstream;
using std::shared_ptr;

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
   * This variable stores the logger used by the lexer to print debug messages.
   */
  shared_ptr<logger> console;

  /**
   * This method add a token stream start symbol to the token queue.
   */
  void scanStart();

public:
  /**
   * @brief This constructor initializes a lexer with the given input.
   *
   * @param stream This stream specifies the text which this lexer analyzes.
   */
  Lexer(ifstream &stream);

  /**
   * @brief This method returns the next token the lexer produced from `input`.
   *
   * @return The next token the parser has not emitted yet
   */
  symbol_type nextToken();
};

#endif // LEXER_HPP
