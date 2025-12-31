#ifndef INCLUDED_VECTOR_
#define INCLUDED_VECTOR_

#include "tuple.hh"

namespace rt
{
  template <Arithmetic Type, size_t Dim>
  class Vector : public Tuple<Type, Dim, Vector> 
  {
  public:
    template <Arithmetic ...Data>
    explicit Vector(Data &&...data)
      : Tuple<Type, Dim, Vector>(std::forward<Data>(data)...)
    {}
  };

  using Vector3i = Vector<int, 3>;
  using Vector3f = Vector<float, 3>;
  using Vector3d = Vector<double, 3>;
};

#endif // INCLUDED_VECTOR_
