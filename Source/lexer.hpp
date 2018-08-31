#ifndef LEXER_HPP
#define LEXER_HPP

// -- Macros -------------------------------------------------------------------

#define SPDLOG_TRACE_ON

#if defined(__clang__)
#define LOGF(fmt, ...)                                                         \
  console->trace("{}:{}: " fmt, __FUNCTION__, __LINE__, __VA_ARGS__)
#else
#define LOGF(fmt, ...)
#endif

#if defined(__clang__)
#define LOG(text) console->trace("{}:{}: {}", __FUNCTION__, __LINE__, text)
#else
#define LOG(text)
#endif

// -- Imports ------------------------------------------------------------------

#include <deque>
#include <fstream>

#if defined(__clang__)
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#endif

#include "input.hpp"
#include "parser.hpp"
#include "symbol.hpp"

#if defined(__clang__)
using spdlog::logger;
using std::shared_ptr;
#endif

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

#if defined(__clang__)
  /**
   * This variable stores the logger used by the lexer to print debug messages.
   */
  shared_ptr<logger> console;
#endif

  /**
   * @brief This method adds the token for the start of the YAML stream to
   *        `tokens`.
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
