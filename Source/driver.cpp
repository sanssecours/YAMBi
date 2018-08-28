#include "driver.hpp"

using std::cerr;
using std::endl;
using std::ios_base;

Driver::Driver() {}
Driver::~Driver() {}

void Driver::error(const location &location, const string &message) {
  cerr << location << ": " << message << '\n';
}

int Driver::parse(const string &filepath) {
  filename = filepath;
  try {
    ifstream{filename};
  } catch (ios_base::failure &fail) {
    cerr << "Unable to read file: " << fail.what() << endl;
  }
  return 0;
}
