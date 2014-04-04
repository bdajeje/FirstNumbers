#include "first_numbers.hpp"

#include "utils/files.hpp"
#include "utils/types.hpp"

#include <boost/thread.hpp>

#include <atomic>
#include <csignal>
#include <mutex>

namespace core {

/*! Shared variable between threads to know when to stop */
std::atomic_bool g_stop;

void signal_handler(int signal_number)
{
  if( signal_number == SIGUSR1 ||
      signal_number == SIGUSR2 )
  {
    std::cout << "Stopping..." << std::endl;
    g_stop = true;
  }
}

bool save(const std::string& filepath, utils::types::nbr result)
{
  // Mutex to access save file
  static std::mutex file_mutex;

  // Lock
  std::lock_guard<std::mutex> lock(file_mutex);

  // Save
  return utils::files::append(filepath, " " + std::to_string(result));
}

/*! Find first number
 *  \warning this function assumes start > 3
 *           We don't test this inside the function for speed purpose (we don't want to test this in every iteration)
 */
utils::types::nbr find(utils::types::nbr start)
{
  // Any number where right digit's different than 1/3/7/9 is not a first number
  auto right_digit = start % 10;
  if( right_digit != 1 &&
      right_digit != 3 &&
      right_digit != 7 &&
      right_digit != 9 )
    return 0;

  utils::types::nbr pos = 3;
  utils::types::nbr end = start / 2;
  while( pos <= end )
  {
    if( start % pos == 0 )
      return 0;

    pos++;
  }

  return start;
}

bool retrieveLastFetchedNumber(const std::string& filepath, utils::types::nbr& result)
{
  std::string content;
  if( !utils::files::read(filepath, content) || content.empty())
    return 0;

  // Find first space from the end
  auto pos = content.length() - 1;
  while( pos >= 2 )
  {
    if(content[pos] == ' ')
      break;

    pos--;
  }

  try
  {
    result = std::stoull( (pos==0) ? content : content.substr(pos) );
  }
  catch(std::invalid_argument&)
  { return false; }
  catch(std::out_of_range&)
  { return false; }

  return true;
}

bool startThread(const std::string& filepath, utils::types::nbr start_from, size_t thread_number, size_t jump)
{
  // Take care of max number value
  auto max = std::numeric_limits<utils::types::nbr>::max() - jump;

  while(!g_stop)
  {
    std::cout << thread_number << " - Testing: " << start_from << std::endl;
    auto found = find(start_from);
    if( found != 0 )
    {
      std::cout << thread_number << " - Found new: " << found << std::endl;
      if(!save(filepath, found))
      {
        std::cout << "Can't save in file: " << filepath << std::endl;
        return false;
      }
    }

    // Number doesn't fit in memory anymore
    if( start_from >= max )
    {
      std::cerr << "Maximum memory number reached: " << max << std::endl;
      break;
    }

    start_from += jump;
  }

  return true;
}

int start(size_t cpu_nbr, const std::string& filepath)
{
  if(cpu_nbr == 0)
    cpu_nbr = 1;

  // Retrieve last found number
  utils::types::nbr start_from = 1;
  if( utils::files::exists(filepath) )
  {
    bool success = retrieveLastFetchedNumber(filepath, start_from);
    if(!success)
    {
      std::cout << "Can't read last number from file: " << filepath << std::endl;
      return EXIT_FAILURE;
    }

    start_from++;
  }
  else if( !utils::files::create(filepath) )
  {
    std::cout << "Can't create file: " << filepath << std::endl;
    return EXIT_FAILURE;
  }

  // Register signal termination
  signal(SIGUSR1, signal_handler);
  signal(SIGUSR2, signal_handler);

  // Let's get rid of numbers 1, 2, 3 which are specific cases
  const short min = 7;
  if( start_from < min )
  {
    save(filepath, 1);
    save(filepath, 2);
    save(filepath, 3);
    save(filepath, 5);
    start_from = min;
  }

  // Start the process
  std::cout << "Starting from: " << start_from << std::endl;
  boost::thread_group threads;
  for( size_t i = 0; i < cpu_nbr; ++i )
    threads.create_thread( boost::bind( startThread, filepath, start_from + i, i+1, cpu_nbr ) );

  threads.join_all();

  return EXIT_SUCCESS;
}

}
