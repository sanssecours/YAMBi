// -- Imports ------------------------------------------------------------------

#include <codecvt>
#include <locale>
#include <sstream>
#include <stdexcept>

#include "input.hpp"

using std::codecvt_utf8;
using std::out_of_range;
using std::stringstream;
using std::wstring_convert;

// -- Class --------------------------------------------------------------------

/**
 * @brief This constructor creates an input from the given stream.
 *
 * @param stream This parameter stores the text this object operates on.
 */
Input::Input(ifstream const &stream) {
  stringstream stringStream;
  stringStream << stream.rdbuf();
  input = wstring_convert<codecvt_utf8<char32_t>, char32_t>{}.from_bytes(
      stringStream.str());
}

/**
 * @brief This function returns a character that was not consumed yet.
 *
 * @param offset This variable specifies the index of the character
 *               this method should retrieve as offset to the last consumed
 *               character.
 *
 * @return A character which is `offset` positions away from the last
 *         consumed character
 */
size_t Input::lookahead(size_t const offset) {
  if (offset == 0 || position + offset > input.size()) {
    return 0;
  }
  return input[position + offset - 1];
}

/**
 * @brief This method consumes the next character of `input`.
 */
void Input::consume() {
  if (position + 1 >= input.size()) {
    throw out_of_range("Unable to consume EOF");
    return;
  }
  position++;
}

/**
 * @brief Retrieve the current position inside the input.
 *
 * @return The current position in number of characters
 */
size_t Input::index() { return position; }
