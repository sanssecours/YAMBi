// -- Imports ------------------------------------------------------------------

#include "convert.hpp"
#include "driver.hpp"

using kdb::Key;
using kdb::KeySet;

// -- Macros -------------------------------------------------------------------

#define STATUS_SYNTAX_ERROR 1
#define STATUS_MEMORY_EXHAUSTION 2

// -- Function -----------------------------------------------------------------

/**
 * @brief This function converts the given YAML file to keys and adds the
 *        result to `keySet`.
 *
 * @param keySet The function adds the converted keys to this variable.
 * @param parent The function uses this parent key of `keySet` to emit error
 *               information.
 * @param filename This parameter stores the path of the YAML file this
 *                 function converts.
 *
 * @retval -1 if there was an error converting the YAML file
 *          0 if parsing was successful and the function did not change the
 *            given keyset
 *          1 if parsing was successful and the function did change `keySet`
 */
int addToKeySet(KeySet &keySet, Key &parent, string const &filename) {
  Driver driver{parent};

  int status = driver.parse(filename);

  if (status == -1 || status == STATUS_SYNTAX_ERROR ||
      status == STATUS_MEMORY_EXHAUSTION) {
    return -1;
  }

  KeySet keys = driver.getKeySet();
  status = (keys.size() <= 0) ? 0 : 1;

  keySet.append(keys);

  return status;
}
