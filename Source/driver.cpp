// -- Imports ------------------------------------------------------------------

#include <cerrno>
#include <fstream>

#include "driver.hpp"

using std::cerr;
using std::endl;

using yy::parser;

// -- Class --------------------------------------------------------------------

/**
 * This function parses the current YAML file.
 *
 * @param filename This parameter stores the path of the file the driver
 *                 should parse.
 *
 * @retval 0 if parsing was successful
 *         EXIT_FAILURE if the driver was unable to open the given file
 *         1 if the given file contains a syntax error
 *         2 if parsing was unsuccessful due to memory exhaustion
 */
int Driver::parse(const string &filepath) {
  filename = filepath;

  ifstream input{filename};
  if (!input.good()) {
    perror(string("Unable to open file “" + filename + "”").c_str());
    return EXIT_FAILURE;
  }

  Lexer lexer{input};
  parser parser{lexer, *this};

  return parser.parse();
}

/**
 * This function will be called by the Bison parser to indicate an error.
 *
 * @param location This value specifies the location of the erroneous input.
 * @param message This value stores the error message emitted by the Bison
 *                parser.
 */
void Driver::error(const location_type &location, const string &message) {
  cerr << location << ": " << message << '\n';
}
