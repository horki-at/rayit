#include "core/logger.hh"
using namespace rt;

#include <string>
#include <iostream>
using namespace std;

int main() try
{
  Logger::initialize(cout);

  Logger::fatal("this is a fatal message. {} {}", 1.2, " hello world");
  Logger::error("this is a error message.");
  Logger::warning("this is a warning message.");
  Logger::info("this is a info message.");
  Logger::debug("this is a debug message.");
  Logger::trace("this is a trace message.");
}
catch (string const &msg)
{
  cout << msg << "\n";
}
