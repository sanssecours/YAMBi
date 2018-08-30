#ifndef CONVERTER_HPP
#define CONVERTER_HPP

// -- Imports ------------------------------------------------------------------

#include <kdb.hpp>

using std::string;

using kdb::Key;
using kdb::KeySet;

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
int addToKeySet(KeySet &keySet, Key &parent, string const &filename);

#endif // CONVERTER_HPP
