#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <fstream>
#include <string>

#include "parser.hpp"

using std::ifstream;
using std::string;

using yy::location;
using yy::parser;

// Declare generated parser function
parser::symbol_type yylex(Driver &driver);

class Driver {
  ifstream file;

public:
  string filename;

  Driver();
  virtual ~Driver();

  int parse(const string &filename);

  // Error handling
  void error(const location &location, const string &message);
};

#endif // DRIVER_HPP
