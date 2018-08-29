#include <cerrno>

#include "driver.hpp"

using std::cerr;
using std::endl;
using std::exception;

using yy::parser;

void Driver::error(const location_type &location, const string &message) {
  cerr << location << ": " << message << '\n';
}

int Driver::parse(const string &filepath) {
  filename = filepath;

  ifstream input{filename};
  if (!input.good()) {
    perror(string("Unable to open file “" + filename + "”").c_str());
    return EXIT_FAILURE;
  }

  lexer = Lexer{input};
  parser parser{*this};

  return parser.parse();
}
