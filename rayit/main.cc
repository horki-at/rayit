#include "logger.h"
#include "tuple.h"
using namespace rt;

#include <string>
#include <iostream>
using namespace std;

int main() try
{
  Logger::initialize(cout);
  
  Vector3f v1(1.f, 2.f, 3.f);
  Vector3i v2(5, 5, 5);
  Vector3f v3 = v1 / 2.0;
  // Vector3i v4(v3);

  Logger::info("The vector sub is {};{};{}", v3.data[0], v3.data[1], v3.data[2]);
}
catch (string const &msg)
{
  cout << msg << "\n";
}
