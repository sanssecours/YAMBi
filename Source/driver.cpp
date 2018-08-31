// -- Imports ------------------------------------------------------------------

#include <cerrno>
#include <fstream>

#include "driver.hpp"

using std::cerr;
using std::endl;

using kdb::Key;
using kdb::KeySet;

using yy::parser;

// -- Macros -------------------------------------------------------------------

#define DEBUG_LEVEL 1

// -- Class --------------------------------------------------------------------

/**
 * This constructor creates a new driver for the given parent key.
 *
 * @param parent This key specifies the parent of the key set the parser
 *               creates.
 */
Driver::Driver(Key const &parent) { parents.push(parent); }

/**
 * @brief This function parses the current YAML file.
 *
 * @param filename This parameter stores the path of the file the driver
 *                 should parse.
 *
 * @retval -3 if the given file could not be opened
 *         -2 if parsing was unsuccessful due to memory exhaustion
 *         -1 if the given file contains a syntax error
 *          0 if parsing was successful
 */
int Driver::parse(const string &filepath) {
  filename = filepath;

  ifstream input{filename};
  if (!input.good()) {
    perror(string("Unable to open file “" + filename + "”").c_str());
    return -3;
  }

  Lexer lexer{input};
  parser parser{lexer, *this};
  parser.set_debug_level(DEBUG_LEVEL);

  return -parser.parse();
}

/**
 * @brief This method retrieves the current key set produced by the driver.
 *
 * @return A key set representing the YAML data produced by the last call of
 *         the method `parse`
 */
KeySet Driver::getKeySet() { return keys; }

/**
 * @brief This function will be called by the Bison parser to indicate an error.
 *
 * @param location This value specifies the location of the erroneous input.
 * @param message This value stores the error message emitted by the Bison
 *                parser.
 */
void Driver::error(const location_type &location, const string &message) {
  cerr << location << ": " << message << '\n';
}

// ===========
// = Actions =
// ===========

/**
 * @brief This function will be called after the parser exits a value.
 *
 * @param text This variable contains the text stored in the value.
 */
void Driver::exitValue(string const &text) {
  Key key = parents.top();
  key.setString(text);
  keys.append(key);
}
