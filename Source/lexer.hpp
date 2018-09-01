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
using std::pair;
using std::unique_ptr;

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
   * This counter stores the number of tokens already emitted by the lexer.
   * The lexer needs this variable, to keep track of the insertion point of
   * `KEY` tokens in the token queue.
   */
  size_t tokensEmitted = 0;

  /**
   * This boolean specifies if the lexer has already scanned the whole input or
   * not.
   */
  bool done = false;

  /**
   * This pair stores a simple key candidate token (first part) and its
   * position in the token queue (second part).
   *
   * Since the lexer only supports block syntax for mappings and sequences we
   * use a single token here. If we need support for flow collections we have
   * to store a candidate for each flow level (block context = flow level 0).
   */
  pair<unique_ptr<Symbol>, size_t> simpleKey;

#if defined(__clang__)
  /**
   * This variable stores the logger used by the lexer to print debug messages.
   */
  shared_ptr<logger> console;
#endif

  /**
   * @brief This method consumes characters from the input stream keeping
   *        track of line and column numbers.
   *
   * @param characters This parameter specifies the number of characters the
   *                   the function should consume.
   */
  void forward(size_t const characters);

  /**
   * @brief This method removes uninteresting characters from the input.
   */
  void scanToNextToken();

  /**
   * @brief This function checks if the lexer needs to scan additional tokens.
   *
   * @retval true If the lexer should fetch additional tokens
   *         false Otherwise
   */
  bool needMoreTokens() const;

  /**
   * @brief This method adds new tokens to the token queue.
   */
  void fetchTokens();

  /**
   * @brief This method checks if the input at the specified offset starts a key
   *        value token.
   *
   * @param offset This parameter specifies an offset to the current position,
   *               where this function will look for a key value token.
   *
   * @retval true If the input matches a key value token
   *         false Otherwise
   */
  bool isValue(size_t const offset = 1) const;

  /**
   * @brief This method checks if the current input starts a list element.
   *
   * @retval true If the input matches a list element token
   *         false Otherwise
   */
  bool isElement() const;

  /**
   * @brief This method checks if the input at the specified offset starts a
   *        line comment.
   *
   * @param offset This parameter specifies an offset to the current position,
   *               where this function will look for a comment token.
   *
   * @retval true If the input matches a comment token
   *         false Otherwise
   */
  bool isComment(size_t const offset) const;

  /**
   * @brief This method saves a token for a simple key candidate located at the
   *        current input position.
   */
  void addSimpleKeyCandidate();

  /**
   * @brief This method adds the token for the start of the YAML stream to
   *        `tokens`.
   */
  void scanStart();

  /**
   * @brief This method adds the token for the end of the YAML stream to
   *        the token queue.
   */
  void scanEnd();

  /**
   * @brief This method scans a plain scalar and adds it to the token queue.
   */
  void scanPlainScalar();

  /**
   * @brief This method counts the number of non space characters that can be
   *        part of a plain scalar at position `offset`.
   *
   * @param offset This parameter specifies an offset to the current input
   *               position, where this function searches for non space
   *               characters.
   *
   * @return The number of non-space characters at the input position `offset`
   */
  size_t countPlainNonSpace(size_t const offset) const;

  /**
   * @brief This method counts the number of space characters that can be part
   *        of a plain scalar at the current input position.
   *
   * @return The number of space characters at the current input position
   */
  size_t countPlainSpace() const;

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
