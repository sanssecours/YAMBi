/**
 * @file
 *
 * @brief This file contains a class that represents textual input.
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#ifndef INPUT_HPP
#define INPUT_HPP

// -- Imports ------------------------------------------------------------------

#include <fstream>

using std::ifstream;
using std::string;
using std::u32string;

// -- Class --------------------------------------------------------------------

class Input {

  /** This variable stores the input represented by this class. */
  u32string input;

  /** This variable stores the current position inside `input`. */
  size_t position = 0;

public:
  /**
   * @brief This constructor creates an input from the given stream.
   *
   * @param stream This parameter stores the text this object operates on.
   */
  Input(ifstream const &stream);

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
  size_t LA(size_t const offset) const;

  /**
   * @brief This method consumes the next character of `input`.
   */
  void consume();

  /**
   * @brief Retrieve the current position inside the input.
   *
   * @return The current position in number of characters
   */
  size_t index() const;

  /**
   * @brief This method retrieves the text between `start` (inclusive) and the
   *         current position (exclusive).
   *
   * @param start This parameter specifies the start index of the string this
   *              functions returns.
   *
   * @return A UTF-8 encoded substring of input starting at `start` and ending
   *         one character before the current position in the input
   */
  string getText(size_t const start) const;
};

#endif // INPUT_HPP
