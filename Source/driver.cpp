#include "driver.hpp"

using std::cerr;

Driver::Driver() {}
Driver::~Driver() {}

void Driver::error(const location &location, const string &message) {
  cerr << location << ": " << message << '\n';
}
