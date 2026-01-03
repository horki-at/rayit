#ifndef INCLUDED_NORMAL_
#define INCLUDED_NORMAL_

#include "tuple.hh"

namespace rt
{
  template <Arithmetic Type, size_t Dim>
  class Normal : public Tuple<Type, Dim, Normal>
  {
  public:
    template <Arithmetic ...Data>
    explicit Normal(Data &&...data)
      : Tuple<Type, Dim, Normal>(std::forward(data)...)
    {}
  };

  using Normal3i = Normal<int, 3>;
  using Normal3f = Normal<float, 3>;
  using Normal3d = Normal<double, 3>;
};

#endif // INCLUDED_NORMAL_
