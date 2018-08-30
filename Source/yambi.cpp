#include <iostream>

#include <kdb.hpp>

#include "convert.hpp"

using ckdb::keyNew;

using std::cerr;
using std::endl;

int main(int argc, char const *argv[]) {

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " filename" << endl;
    return EXIT_FAILURE;
  }

  string filename = argv[1];

  KeySet keys;
  Key parent{keyNew("user", KEY_END, "", KEY_VALUE)};

  return (addToKeySet(keys, parent, filename) >= 0) ? EXIT_SUCCESS
                                                    : EXIT_FAILURE;
}
