#ifndef INPUT_HPP
#define INPUT_HPP

// -- Imports ------------------------------------------------------------------

#include <fstream>

using std::ifstream;
using std::u32string;

// -- Class --------------------------------------------------------------------

class Input {

  /** This variable stores the input represented by this class. */
  u32string input;

  /** This variable stores the current position inside `input`. */
  size_t position;

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
  size_t lookahead(size_t const offset);

  /**
   * @brief This method consumes the next character of `input`.
   */
  void consume();

  /**
   * @brief Retrieve the current position inside the input.
   *
   * @return The current position in number of characters
   */
  size_t index();
};

#endif // INPUT_HPP
