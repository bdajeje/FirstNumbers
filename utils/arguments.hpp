#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <string>

namespace utils {
namespace args {
  const std::string CPU  = "-c";
  const std::string FILE = "-f";
}

/*! Retrieve number of CPU cores to use
 *  The user could define a precison number of cpu to use like "-c 3" (to use 3 cpus)
 *  By default the application will use as many as possible cpu cores
 *  \param argc from main
 *  \param argv from main
 *  \return number of CPU cores to use
 */
size_t retrieveCPUNbr(int argc, char** argv);

/*! Retrieve filepath where to load/save results
 *  \param argc from main
 *  \param argv from main
 *  \return filepath where to load/save results or empty string on error
 */
std::string retrieveSaveFilepath(int argc, char** argv);

}

#endif // ARGUMENTS_HPP
