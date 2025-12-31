#ifndef INCLUDED_TUPLE_
#define INCLUDED_TUPLE_

#include <utility>
#include <array>

namespace rt
{
  template <typename Type>
  concept Arithmetic = std::is_arithmetic_v<std::remove_cvref_t<Type>>;

  template <template <Arithmetic, size_t> class Lhs, template <Arithmetic, size_t> class Rhs>
  struct TupleCanAdd : std::false_type {};

  template <template <Arithmetic, size_t> class Lhs, template <Arithmetic, size_t> class Rhs>
  struct TupleCanSub : std::false_type {};
  
  // Tuple is a collection of arithmetic dim elements (i.e., Dim-dimensional
  // list).  This class provides general mathematical operations commonly
  // associated with tuples such as element-wise addition and scalar
  // multiplication.  By default, derived tuple classes have no access to those
  // operations. This must be specified in TupleCanOp type logic table.
  //
  // Dim: number of elements in the tuple.
  // Arithmetic: formal arithmetic type of the underlying tuple elements.
  // Derived: the class that *this Tuple is derived from.
  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  class Tuple
  {
    std::array<Type, Dim> d_data;

    using iterator = std::array<Type, Dim>::iterator;
    using const_iterator = std::array<Type, Dim>::const_iterator;
    
  public:                       // constructors
    Tuple() = default;

    template <Arithmetic ...Data>
    requires (sizeof...(Data) == Dim)
    Tuple(Data &&...data);

    Tuple(Tuple const &) = default;
    Tuple(Tuple &&) = default;
    Tuple &operator=(Tuple const &) = default;
    Tuple &operator=(Tuple &&) = default;

    void swap(Tuple &other) noexcept;
    virtual ~Tuple() = default;

  public:
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    Type &operator[](size_t idx);
    Type const &operator[](size_t idx) const;

    template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
    requires TupleCanAdd<Derived, Rhs>::value
    Derived<Type, Dim> &operator+=(Rhs<RhsType, Dim> rhs);
    
    template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
    requires TupleCanSub<Derived, Rhs>::value
    Derived<Type, Dim> &operator-=(Rhs<RhsType, Dim> rhs);

    template <Arithmetic RhsType>
    Derived<Type, Dim> &operator*=(RhsType factor);

    template <Arithmetic RhsType>
    Derived<Type, Dim> &operator/=(RhsType factor);

    Derived<Type, Dim> operator-() const;
    void negate();              // negate this object 

  private:
    template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
    void add(Rhs<RhsType, Dim> rhs);

    template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
    void sub(Rhs<RhsType, Dim> rhs);

    template <Arithmetic RhsType>
    void mul(RhsType factor);

    template <Arithmetic RhsType>
    void div(RhsType factor);

  };
};

namespace rt
{                               // forward declarations
  template <Arithmetic Type, size_t Dim> class Vector;
  template <Arithmetic Type, size_t Dim> class Point;
  template <Arithmetic Type, size_t Dim> class Normal;

                                // which tuple-derived class can ADD with each other
  template <> struct TupleCanAdd<Vector, Vector> : std::true_type {}; // V + V => V
  template <> struct TupleCanAdd<Point, Vector> : std::true_type {};  // P + V => P
  template <> struct TupleCanAdd<Point, Normal> : std::true_type {};  // P + N => P
                                // which tuple-derived class can SUB with each other
  template <> struct TupleCanSub<Vector, Vector> : std::true_type {}; // V - V => V
  template <> struct TupleCanSub<Point, Vector> : std::true_type {}; // P - V => P
  template <> struct TupleCanSub<Point, Normal> : std::true_type {}; // P - N => P
                                // P - P => V, this is implemented in rt::Point
};

#include "tuple.inl"
#include "tuple.tpp"
#endif // INCLUDED_TUPLE_
