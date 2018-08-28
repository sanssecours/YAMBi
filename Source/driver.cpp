#include <cerrno>

#include "driver.hpp"

using std::cerr;
using std::endl;
using std::exception;

using yy::parser;

Driver::Driver() {}
Driver::~Driver() {}

void Driver::error(const location &location, const string &message) {
  cerr << location << ": " << message << '\n';
}

int Driver::parse(const string &filepath) {
  filename = filepath;

  file = ifstream{filename};
  if (!file.good()) {
    perror(string("Unable to open file “" + filename + "”").c_str());
    return EXIT_FAILURE;
  }

  parser parser{*this};

  return parser.parse();
}
