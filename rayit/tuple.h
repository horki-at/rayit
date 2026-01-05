#ifndef INCLUDED_TUPLE_
#define INCLUDED_TUPLE_

#include <functional>
#include <algorithm>
#include <cstring>

// TODO: write tests for all Tuple-derived classes
// TODO: write Vector (dot, cross, length, norm, unit)
// TODO: write Point (???)
// TODO: write Color (???)
// TODO: create std::formatter for Tuples
namespace rt
{
  template <typename U>
  concept Arithmetic = std::is_arithmetic_v<std::remove_cvref_t<U>>;

  template <template <Arithmetic, size_t> class T1,
            template <Arithmetic, size_t> class T2>
  struct TupleAdd
  {
    static constexpr bool defined = false; // by default, T1 + T2 is forbidden.
    // provide template <Arithmetic, size_t> type in the specialization
  };

  template <template <Arithmetic, size_t> class T1,
            template <Arithmetic, size_t> class T2>
  struct TupleSub
  {
    static constexpr bool defined = false; // by default, T1 - T2 is forbidden.
    // provide template <Arithmetic, size_t> type in the specialization
  };

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  class Tuple
  {
  public:
    std::array<U, D> data;      // D-dimensional array of element of type U

  public:
    constexpr Tuple() = default; // by default, the tuple is 0-initialized

    template <Arithmetic ...Data>
    requires (sizeof...(Data) == D)
    explicit constexpr Tuple(Data &&...data): data{ std::forward<Data>(data)... } {}

    template <template <Arithmetic, size_t> class To>
    explicit constexpr Tuple(To<U, D> const &other): data{ other.data } {}

    template <template <Arithmetic, size_t> class To>
    explicit constexpr Tuple(To<U, D> &&other): data{ std::move(other.data) } {}
    
    constexpr Tuple(Tuple const &)            = default;
    constexpr Tuple(Tuple &&)                 = default;
    constexpr Tuple &operator=(Tuple const &) = default;
    constexpr Tuple &operator=(Tuple &&)      = default;
    constexpr ~Tuple()                        = default;

    void swap(Tuple<U, D, T> &other) noexcept;

  public:
    template <Arithmetic Uo, template <Arithmetic, size_t> class To>
    requires (TupleAdd<T, To>::defined)
    constexpr T<U, D> &operator+=(To<Uo, D> other);

    template <Arithmetic Uo, template <Arithmetic, size_t> class To>
    requires (TupleSub<T, To>::defined)
    constexpr T<U, D> &operator-=(To<Uo, D> other);

    template <Arithmetic Uo>
    constexpr T<U, D> &operator*=(Uo scalar);

    template <Arithmetic Uo>
    constexpr T<U, D> &operator/=(Uo scalar);

    template <Arithmetic Uo>
    constexpr T<U, D> operator*(Uo scalar);

    template <Arithmetic Uo>
    constexpr T<U, D> operator/(Uo scalar);

  private:
    template <Arithmetic Uo, template <Arithmetic, size_t> class To>
    constexpr void add(To<Uo, D> other);

    template <Arithmetic Uo, template <Arithmetic, size_t> class To>
    constexpr void sub(To<Uo, D> other);

    template <Arithmetic Uo>
    constexpr void mul(Uo scalar);

    template <Arithmetic Uo>
    constexpr void div(Uo scalar);
  };

  template <Arithmetic U1, Arithmetic U2, size_t D,
            template <Arithmetic, size_t> class T1,
            template <Arithmetic, size_t> class T2>
  requires (TupleAdd<T1, T2>::defined)
  constexpr auto operator+(T1<U1, D> tuple1, T2<U2, D> tuple2)
  {
    using CommonU = std::common_type_t<U1, U2>;
    using ResultT = typename TupleAdd<T1, T2>::template type<CommonU, D>;

    if constexpr (std::is_same_v<ResultT, T1<U1, D>>)
      return tuple1 += tuple2;
    else if constexpr (std::is_same_v<ResultT, T2<U2, D>>)
      return tuple2 += tuple1;
    else
      return ResultT(tuple1) += tuple2;
  }

  template <Arithmetic U1, Arithmetic U2, size_t D,
            template <Arithmetic, size_t> class T1,
            template <Arithmetic, size_t> class T2>
  requires (TupleSub<T1, T2>::defined)
  constexpr auto operator-(T1<U1, D> tuple1, T2<U2, D> tuple2)
  {
    using CommonU = std::common_type_t<U1, U2>;
    using ResultT = typename TupleSub<T1, T2>::template type<CommonU, D>;

    if constexpr (std::is_same_v<ResultT, T1<U1, D>>)
      return tuple1 -= tuple2;
    else
      return ResultT(tuple1) -= tuple2;
  }

  template <Arithmetic U, size_t D>
  class Vector : public Tuple<U, D, Vector>
  {
  public:
    using Tuple<U, D, Vector>::Tuple;
  };
};

namespace rt
{
  using Vector2i = Vector<int, 2>;
  using Vector3i = Vector<int, 3>;
  using Vector4i = Vector<int, 4>;

  using Vector2f = Vector<float, 2>;
  using Vector3f = Vector<float, 3>;
  using Vector4f = Vector<float, 4>;

  using Vector2d = Vector<double, 2>;
  using Vector3d = Vector<double, 3>;
  using Vector4d = Vector<double, 4>;
};

namespace rt
{
  template <> struct TupleAdd<Vector, Vector> // Vector + Vector => Vector
  {
    static constexpr bool defined = true;
    template <Arithmetic U, size_t D> using type = Vector<U, D>;
  };

  template <> struct TupleSub<Vector, Vector> // Vector - Vector => Vector
  {
    static constexpr bool defined = true;
    template <Arithmetic U, size_t D> using type = Vector<U, D>;
  };
};

namespace rt
{
  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  void Tuple<U, D, T>::swap(Tuple<U, D, T> &other) noexcept
  {
    size_t const size = sizeof(Tuple<U, D, T>);
    char buffer[size];
    memcpy(buffer, static_cast<void *>(&other), size);
    memcpy(static_cast<void *>(this), buffer, size);
    memcpy(static_cast<void *>(&other), this, size);
  }
  
  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo, template <Arithmetic, size_t> class To>
  requires (TupleAdd<T, To>::defined)
  inline constexpr T<U, D> &Tuple<U, D, T>::operator+=(To<Uo, D> other)
  {                             // Check that addition makes sense
    using ResultT = typename TupleAdd<T, To>::template type<U, D>;
    static_assert(std::is_same_v<ResultT, T<U, D>>,
      "Invalid +=: adding this type would change the underlying type of this Tuple.");

    add(other);
    return static_cast<T<U, D> &>(*this);
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo, template <Arithmetic, size_t> class To>
  requires (TupleSub<T, To>::defined)
  inline constexpr T<U, D> &Tuple<U, D, T>::operator-=(To<Uo, D> other)
  {                             // Check that subtraction makes sense
    using ResultT = typename TupleSub<T, To>::template type<U, D>;
    static_assert(std::is_same_v<ResultT, T<U, D>>,
      "Invalid -=: adding this type would change the underlying type of this Tuple.");

    sub(other);
    return static_cast<T<U, D> &>(*this);
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo>
  inline constexpr T<U, D> &Tuple<U, D, T>::operator*=(Uo scalar)
  {
    mul(scalar);
    return static_cast<T<U, D> &>(*this);
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo>
  constexpr T<U, D> &Tuple<U, D, T>::operator/=(Uo scalar)
  {
    Tuple<U, D, T> cpy(*this);
    cpy.div(scalar);
    this->swap(cpy);
    return static_cast<T<U, D> &>(*this);
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo>
  inline constexpr T<U, D> Tuple<U, D, T>::operator*(Uo scalar)
  {
    return static_cast<T<U, D>>(Tuple<U, D, T>(*this) *= scalar);
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo>
  inline constexpr T<U, D> Tuple<U, D, T>::operator/(Uo scalar)
  {
    return static_cast<T<U, D>>(Tuple<U, D, T>(*this) /= scalar);
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo, template <Arithmetic, size_t> class To>
  inline constexpr void Tuple<U, D, T>::add(To<Uo, D> other)
  {
    std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::plus<>{});
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo, template <Arithmetic, size_t> class To>
  inline constexpr void Tuple<U, D, T>::sub(To<Uo, D> other)
  {
    std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::minus<>{});
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo>
  inline constexpr void Tuple<U, D, T>::mul(Uo scalar)
  {
    std::transform(data.begin(), data.end(), data.begin(),
                   [scalar](U &el)
                   {
                     return el * scalar;
                   });
  }

  template <Arithmetic U, size_t D, template <Arithmetic, size_t> class T>
  template <Arithmetic Uo>
  constexpr void Tuple<U, D, T>::div(Uo scalar)
  {
    if (not scalar)             // scalar is 0
      throw std::invalid_argument("division by zero in tuple");

    std::transform(data.begin(), data.end(), data.begin(),
                   [scalar](U &el)
                   {
                     return el / scalar;
                   });
  }
};

#endif // INCLUDED_TUPLE_
