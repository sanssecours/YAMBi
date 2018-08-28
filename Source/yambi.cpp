#include <iostream>

#include "driver.hpp"

using std::cerr;
using std::endl;

int main(int argc, char const *argv[]) {

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " filename" << endl;
    return EXIT_FAILURE;
  }

  string filename = argv[1];
  Driver driver;

  return driver.parse(filename);
}
