#ifndef DRIVER_HPP
#define DRIVER_HPP

// -- Imports ------------------------------------------------------------------

#include <string>

#include <kdb.hpp>

#include "lexer.hpp"
#include "parser.hpp"

using std::string;

using kdb::KeySet;

using location_type = yy::parser::location_type;

// -- Class --------------------------------------------------------------------

class Driver {

  /** This variable stores the key set the drive creates from the given YAML
      file */
  KeySet keys;

public:
  /** This variable stores the path of the YAML file the driver is parsing. */
  string filename;

  /**
   * @brief This function parses the current YAML file.
   *
   * @param filename This parameter stores the path of the file the driver
   *                 should parse.
   *
   * @retval -1 if the given file could not be opened
   *          0 if parsing was successful
   *          1 if the given file contains a syntax error
   *          2 if parsing was unsuccessful due to memory exhaustion
   */
  int parse(const string &filepath);

  /**
   * @brief This method retrieves the current key set produced by the driver.
   *
   * @return A key set representing the YAML data produced by the last call of
   *         the method `parse`
   */
  KeySet getKeySet();

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
