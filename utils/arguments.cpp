#include "arguments.hpp"

#include <thread>

namespace utils {

size_t getNbrCPUs()
{
  size_t nbr_cpus = std::thread::hardware_concurrency();

  if( nbr_cpus < 1 ) // Just to be safe
    return 1;
  else return nbr_cpus;
}

std::string findArg(int argc, char** argv, const std::string& arg_name)
{
  for(int i = 1; i < argc; i+=2)
  {
    if(std::string(argv[i]) == arg_name && i+1 < argc)
      return argv[i+1];
  }

  return {};
}

size_t retrieveUserCPUNbr(int argc, char** argv)
{
  static const size_t error = 0;

  // Find CPU argument
  try
  {
    return std::stoul(findArg(argc, argv, args::CPU));
  }
  catch(std::invalid_argument&)
  { return error; }
  catch(std::out_of_range&)
  { return error; }

  return error;
}

size_t retrieveCPUNbr(int argc, char** argv)
{
  const auto user_cpu_nbr = retrieveUserCPUNbr(argc, argv);

  return (user_cpu_nbr > 0) ? user_cpu_nbr : getNbrCPUs();
}

std::string retrieveSaveFilepath(int argc, char** argv)
{
  if( argc < 3 )
    return {};

  return findArg(argc, argv, args::FILE);
}

} // namespace utils
