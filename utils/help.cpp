#include "help.hpp"

namespace utils {

std::string getHelp()
{
  return R"TEXT(
  NombresPremiers allows you to retrieve mathematical first numbers.
  The program uses as many available cpu cores (or user defined input) to calculate.
  Results are saved in a file.
  The program starts from its last found result.

  Usage:
    ./NombresPremiers -f save_file [-c nbr_cpu_cores]
      )TEXT";
}

}
