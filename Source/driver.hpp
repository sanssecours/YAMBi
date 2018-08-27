#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "parser.hpp"
#include <string>

using std::string;

using yy::location;
using yy::parser;

// Declare generated parser function
parser::symbol_type yylex(Driver &driver);

class Driver {
public:
  string filename;

  Driver();
  virtual ~Driver();

  // Error handling
  void error(const location &location, const string &message);
};

#endif // DRIVER_HPP
