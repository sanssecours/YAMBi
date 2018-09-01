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
    if (input.LA(1) == 0) {
      LOG("Hit EOF!");
      return;
    }

    location += 1;
    if (input.LA(1) == '\n') {
      location.end.column = 1;
      location.lines();
    }
    input.consume();
  }
}

/**
 * @brief This function checks if the lexer needs to scan additional tokens.
 *
 * @retval true If the lexer should fetch additional tokens
 *         false Otherwise
 */
bool Lexer::needMoreTokens() const {
  if (done) {
    return false;
  }

  bool keyCandidateExists = simpleKey.first != nullptr;
  return keyCandidateExists || tokens.empty();
}

/**
 * @brief This method removes uninteresting characters from the input.
 */
void Lexer::scanToNextToken() {
  LOG("Scan to next token");
  bool found = false;
  while (!found) {
    while (input.LA(1) == ' ') {
      forward();
    }
    LOG("Skipped whitespace");
    if (input.LA(1) == '\n') {
      forward();
      LOG("Skipped newline");
    } else {
      found = true;
      LOG("Found next token");
    }
  }
}

/**
 * @brief This method adds new tokens to the token queue.
 */
void Lexer::fetchTokens() {
  scanToNextToken();
  location.step();

  if (input.LA(1) == 0) {
    scanEnd();
    return;
  }

  scanPlainScalar();
}

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
bool Lexer::isValue(size_t const offset) const {
  return (input.LA(offset) == ':') &&
         (input.LA(offset + 1) == '\n' || input.LA(offset + 1) == ' ');
}

/**
 * @brief This method checks if the current input starts a list element.
 *
 * @retval true If the input matches a list element token
 *         false Otherwise
 */
bool Lexer::isElement() const {
  return (input.LA(1) == '-') && (input.LA(2) == '\n' || input.LA(2) == ' ');
}

/**
 * @brief This method checks if the input at the specified offset starts a line
 *        comment.
 *
 * @param offset This parameter specifies an offset to the current position,
 *               where this function will look for a comment token.
 *
 * @retval true If the input matches a comment token
 *         false Otherwise
 */
bool Lexer::isComment(size_t const offset) const {
  return (input.LA(offset) == '#') &&
         (input.LA(offset + 1) == '\n' || input.LA(offset + 1) == ' ');
}

/**
 * @brief This method saves a token for a simple key candidate located at the
 *        current input position.
 */
void Lexer::addSimpleKeyCandidate() {
  size_t position = tokens.size() + tokensEmitted;
  simpleKey = make_pair(
      unique_ptr<Symbol>(new Symbol{token::TOKEN_KEY, location, "KEY"}),
      position);
}

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
  tokens.push_back(Symbol(token::TOKEN_END, location));
  done = true;
}

/**
 * @brief This method scans a plain scalar and adds it to the token queue.
 */
void Lexer::scanPlainScalar() {
  LOG("Scan plain scalar");
  // A plain scalar can start a simple key
  addSimpleKeyCandidate();

  size_t lengthSpace = 0;
  size_t lengthNonSpace = 0;
  size_t start = input.index();

  while (true) {
    lengthNonSpace = countPlainNonSpace(lengthSpace);
    if (lengthNonSpace == 0) {
      break;
    }
    forward(lengthSpace + lengthNonSpace);
    lengthSpace = countPlainSpace();
  }

  tokens.push_back(
      Symbol(token::TOKEN_PLAIN_SCALAR, location, input.getText(start)));
}

/**
 * @brief This method counts the number of non space characters that can be part
 *        of a plain scalar at position `offset`.
 *
 * @param offset This parameter specifies an offset to the current input
 *               position, where this function searches for non space
 *               characters.
 *
 * @return The number of non-space characters at the input position `offset`
 */
size_t Lexer::countPlainNonSpace(size_t const offset) const {
  LOG("Scan non space characters");
  string const stop = " \n";

  size_t lookahead = offset + 1;
  while (stop.find(input.LA(lookahead)) == string::npos &&
         input.LA(lookahead) != 0 && !isValue(lookahead) &&
         !isComment(lookahead)) {
    lookahead++;
  }

  LOGF("Found {} non-space characters", lookahead - offset - 1);
  return lookahead - offset - 1;
}

/**
 * @brief This method counts the number of space characters that can be part
 *        of a plain scalar at the current input position.
 *
 * @return The number of space characters at the current input position
 */
size_t Lexer::countPlainSpace() const {
  LOG("Scan spaces");
  size_t lookahead = 1;
  while (input.LA(lookahead) == ' ') {
    lookahead++;
  }
  LOGF("Found {} space characters", lookahead - 1);
  return lookahead - 1;
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
}

/**
 * @brief This method returns the next token the lexer produced from `input`.
 *
 * @return The next token the parser has not emitted yet
 */
parser::symbol_type Lexer::nextToken() {
  while (needMoreTokens()) {
    fetchTokens();
    LOG("Tokens:");
    for (auto token : tokens) {
      LOGF("\t {}", token.toString());
    }
  }

  // If `fetchTokens` was unable to retrieve a token (error condition), we emit
  // an end token.
  if (tokens.size() <= 0) {
    tokens.push_back(Symbol(token::TOKEN_END, location));
  }
  Symbol token = tokens.front();
  tokens.pop_front();
  tokensEmitted++;
  return token.get();
}
