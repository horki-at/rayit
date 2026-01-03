#ifndef INCLUDED_VECTOR_
#define INCLUDED_VECTOR_

#include "tuple.hh"

#include <numeric>
#include <cmath>

namespace rt
{
  // Custom type for length of a Vector.
  template <Arithmetic Type> struct VectorLengthType { using type = float; };
  template <> struct VectorLengthType<double> { using type = double; };
  
  template <Arithmetic Type, size_t Dim>
  class Vector : public Tuple<Type, Dim, Vector> 
  {
  public:
    template <Arithmetic ...Data>
    explicit Vector(Data &&...data)
      : Tuple<Type, Dim, Vector>(std::forward<Data>(data)...)
    {}
    
    template <Arithmetic OtherType>
    Type dot(Vector<OtherType, Dim> other) const;

    template <Arithmetic OtherType>
    Vector<Type, Dim> cross(Vector<OtherType, Dim> other) const;

    VectorLengthType<Type>::type length() const;

    void norm();                    // normalize this vector
    Vector<Type, Dim> unit() const; // get a new normalized unit vector from *this
  };

  using Vector3i = Vector<int, 3>;
  using Vector3f = Vector<float, 3>;
  using Vector3d = Vector<double, 3>;
};

#include "vector.inl"
#include "vector.tpp"
#endif // INCLUDED_VECTOR_
