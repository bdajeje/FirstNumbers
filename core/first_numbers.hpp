#ifndef FIRST_NUMBERS_HPP
#define FIRST_NUMBERS_HPP

#include <iostream>
#include <string>

namespace core {

/*! Start to retrieve first numbers
 *  If previously fetched data are retrieved, calculs start from where they stoped.
 *  If the given file doesn't exist, calculs start from 0 and are saved in this file.
 *  If the file exists but the data can't be retrieved, the function exit with error code.
 *  \param cpu_nbr to use in parallel
 *  \param filepath where to load/save the results
 */
int start(size_t cpu_nbr, const std::string& filepath);

}

#endif // FIRST_NUMBERS_HPP
