#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <fstream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"

using std::string;

using location_type = yy::parser::location_type;

class Driver {
public:
  string filename;
  Lexer lexer;

  int parse(const string &filename);

  // Error handling
  void error(const location_type &location, const string &message);
};

#endif // DRIVER_HPP
