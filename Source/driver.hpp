#ifndef DRIVER_HPP
#define DRIVER_HPP

// -- Imports ------------------------------------------------------------------

#include <string>

#include "lexer.hpp"
#include "parser.hpp"

using std::string;

using location_type = yy::parser::location_type;

// -- Class --------------------------------------------------------------------

class Driver {
public:
  /** This variable stores the path of the YAML file the driver is parsing. */
  string filename;

  /**
   * @brief This function parses the current YAML file.
   *
   * @param filename This parameter stores the path of the file the driver
   *                 should parse.
   *
   * @retval 0 if parsing was successful
   *         EXIT_FAILURE if the driver was unable to open the given file
   *         1 if the given file contains a syntax error
   *         2 if parsing was unsuccessful due to memory exhaustion
   */
  int parse(const string &filename);

  /**
   * @brief This function will be called by the Bison parser to indicate an
   *        error.
   *
   * @param location This value specifies the location of the erroneous input.
   * @param message This value stores the error message emitted by the Bison
   *                parser.
   */
  void error(const location_type &location, const string &message);
};

#endif // DRIVER_HPP
