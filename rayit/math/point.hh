#ifndef INCLUDED_POINT_
#define INCLUDED_POINT_

#include "tuple.hh"

namespace rt
{
  template <Arithmetic Type, size_t Dim>
  class Point : public Tuple<Type, Dim, Point>
  {
  public:
    template <Arithmetic ...Data>
    explicit Point(Data &&...data)
      : Tuple<Type, Dim, Point>(std::forward(data)...)
    {}
  };

  using Point3i = Point<int, 3>;
  using Point3f = Point<float, 3>;
  using Point3d = Point<double, 3>;
};

#endif // INCLUDED_POINT_
