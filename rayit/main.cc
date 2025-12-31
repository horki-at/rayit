#include "core/logger.hh"
#include "math/vector.hh"
#include "math/point.hh"
using namespace rt;

#include <string>
#include <iostream>
using namespace std;

int main() try
{
  Logger::initialize(cout);

  Vector3i v0(5, 5, 5);
  Vector3i v1(1, 2, 3);

  Logger::info("The vector v0 is [{};{};{}]", v0[0], v0[1], v0[2]);
  Logger::info("The vector v1 is [{};{};{}]", v1[0], v1[1], v1[2]);

  v0 += v1;

  Logger::info("The vector v0 is [{};{};{}]", v0[0], v0[1], v0[2]);
  Logger::info("The vector v1 is [{};{};{}]", v1[0], v1[1], v1[2]);

  ((v0 -= v1) *= 2).negate();

  Logger::info("The vector v0 is [{};{};{}]", v0[0], v0[1], v0[2]);
  Logger::info("The vector v1 is [{};{};{}]", v1[0], v1[1], v1[2]);

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
