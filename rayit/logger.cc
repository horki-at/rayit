#include "logger.h"
using namespace rt;

#include <stdexcept>
using namespace std;

bool Logger::s_initialized = false;

//static
void Logger::initialize(ostream &out, bool verbose)
{
  if (s_initialized)
    fatal("logger double initialization.");

  s_initialized = true;
  Logger &logger = instance();
  logger.d_out = &out;
  logger.d_verbose = verbose;
}

//static
Logger &Logger::instance()
{
  static Logger s_logger;

  if (not s_initialized)
    throw std::runtime_error("Tried to get an instance of an uninitialized logger.");

  return s_logger;
}

//static
char const *Logger::getLevelString(Level level)
{
  static char const *s_levelStrings[] = {
    "FATAL",                    // Logger::Level::Fatal
    "ERROR",                    // Logger::Level::Error
    "WARNING",                  // Logger::Level::Warning
    "INFO",                     // Logger::Level::Info
    "DEBUG",                    // Logger::Level::Debug
    "TRACE"                     // Logger::Level::Trace
  };

  return s_levelStrings[level];
}
