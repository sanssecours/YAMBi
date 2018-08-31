#include <iostream>

#include <kdb.hpp>

#include "convert.hpp"

using ckdb::keyNew;

using std::cerr;
using std::cout;
using std::endl;

void printOutput(KeySet const &keys) {
  cout << "— Output ————" << endl << endl;
  for (auto key : keys) {
    cout << key.getName() << ":"
         << (key.getStringSize() > 1 ? " " + key.getString() : "") << endl;
  }
}

int main(int argc, char const *argv[]) {

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " filename" << endl;
    return EXIT_FAILURE;
  }

  string filename = argv[1];

  KeySet keys;
  Key parent{keyNew("user", KEY_END, "", KEY_VALUE)};

  int status = addToKeySet(keys, parent, filename);
  printOutput(keys);
  return (status >= 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
