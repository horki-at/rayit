/*
 * Version 0.0.1 - implemented logging (31/12/2025, @horki-at)
 */

#include "logger.hh"
using namespace rt;

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() try
{
  ofstream stream("report.log");
  if (not stream)
    throw "cannot open stream."s;

  Logger::initialize(stream, true);

  Logger::fatal("this is a fatal message.");
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
