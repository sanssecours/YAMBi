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

Lexer::Lexer() {}
Lexer::~Lexer() {}

size_t Lexer::lookahead(size_t offset) {
  if (offset == 0 || position + offset > input.size()) {
    return 0;
  }
  return input[static_cast<size_t>(position + offset - 1)];
}

void Lexer::consume() {
  if (position + 1 >= input.size()) {
    throw out_of_range("Unable to consume EOF");
    return;
  }
  position++;
}

Lexer::Lexer(ifstream &stream) {
  scanStart();
  stringstream stringStream;
  stringStream << stream.rdbuf();
  input = wstring_convert<codecvt_utf8<char32_t>, char32_t>{}.from_bytes(
      stringStream.str());
}

parser::symbol_type Lexer::nextToken() {
  if (tokens.size() < 1) {
    return parser::make_END(location);
  }

  Symbol next = tokens.front();
  tokens.pop_front();
  return next.get();
}

/**
 * @brief This method adds the token for the start of the YAML stream to
 *        `tokens`.
 */
void Lexer::scanStart() {
  tokens.push_back(Symbol(token::TOKEN_STREAM_START, location, "STREAM START"));
}
