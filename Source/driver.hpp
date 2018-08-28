#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <fstream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"

using std::ifstream;
using std::string;

using yy::location;

class Driver {
public:
  string filename;
  Lexer lexer;

  Driver();
  virtual ~Driver();

  int parse(const string &filename);

  // Error handling
  void error(const location &location, const string &message);
};

#endif // DRIVER_HPP
