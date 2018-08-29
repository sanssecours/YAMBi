// -- Imports ------------------------------------------------------------------

#include <codecvt>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "lexer.hpp"

using std::codecvt_utf8;
using std::out_of_range;
using std::stringstream;
using std::wstring_convert;

using yy::parser;

using location_type = parser::location_type;
using token = parser::token;

// -- Class --------------------------------------------------------------------

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
size_t Lexer::lookahead(size_t offset) {
  if (offset == 0 || position + offset > input.size()) {
    return 0;
  }
  return input[static_cast<size_t>(position + offset - 1)];
}

/**
 * This method consumes the next character of `input`.
 */
void Lexer::consume() {
  if (position + 1 >= input.size()) {
    throw out_of_range("Unable to consume EOF");
    return;
  }
  position++;
}

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
Lexer::Lexer(ifstream &stream) {
  scanStart();
  stringstream stringStream;
  stringStream << stream.rdbuf();
  input = wstring_convert<codecvt_utf8<char32_t>, char32_t>{}.from_bytes(
      stringStream.str());
}

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
