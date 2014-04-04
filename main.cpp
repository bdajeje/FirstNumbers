#include <iostream>

#include "utils/arguments.hpp"
#include "utils/help.hpp"

#include "core/first_numbers.hpp"

int main(int argc, char** argv)
{
  const std::string filepath = utils::retrieveSaveFilepath(argc, argv);
  if(filepath.empty())
  {
    std::cout << utils::getHelp() << std::endl;
    return EXIT_FAILURE;
  }

  const auto cpu_nbr = utils::retrieveCPUNbr(argc, argv);

  std::cout << "Starting application with " << cpu_nbr << " cpu cores" << std::endl;

  return core::start(cpu_nbr, filepath);
}

