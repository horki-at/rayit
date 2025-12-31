namespace rt
{
  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic ...Data>
  requires (sizeof...(Data) == Dim)
  inline Tuple<Type, Dim, Derived>::Tuple(Data &&...data)
    : d_data{ std::forward<Data>(data)... }
  {
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline Tuple<Type, Dim, Derived>::iterator Tuple<Type, Dim, Derived>::begin()
  {
    return d_data.begin();
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline Tuple<Type, Dim, Derived>::const_iterator Tuple<Type, Dim, Derived>::begin() const
  {
    return d_data.begin();
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline Tuple<Type, Dim, Derived>::iterator Tuple<Type, Dim, Derived>::end()
  {
    return d_data.end();
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline Tuple<Type, Dim, Derived>::const_iterator Tuple<Type, Dim, Derived>::end() const
  {
    return d_data.end();
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline Type &Tuple<Type, Dim, Derived>::operator[](size_t idx)
  {
    return d_data[idx];
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline Type const &Tuple<Type, Dim, Derived>::operator[](size_t idx) const
  {
    return d_data[idx];
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
  requires TupleCanAdd<Derived, Rhs>::value
  inline Derived<Type, Dim> &Tuple<Type, Dim, Derived>::operator+=(Rhs<RhsType, Dim> rhs)
  {
    add(rhs);
    return static_cast<Derived<Type, Dim> &>(*this);
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
  requires TupleCanSub<Derived, Rhs>::value
  inline Derived<Type, Dim> &Tuple<Type, Dim, Derived>::operator-=(Rhs<RhsType, Dim> rhs)
  {
    sub(rhs);
    return static_cast<Derived<Type, Dim> &>(*this);
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType>
  inline Derived<Type, Dim> &Tuple<Type, Dim, Derived>::operator*=(RhsType factor)
  {
    mul(factor);
    return static_cast<Derived<Type, Dim> &>(*this);
  }


  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
  inline void Tuple<Type, Dim, Derived>::add(Rhs<RhsType, Dim> rhs)
  {
    std::transform(rhs.begin(), rhs.end(), begin(), begin(), std::plus<>{});
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType, template <Arithmetic, size_t> class Rhs>
  inline void Tuple<Type, Dim, Derived>::sub(Rhs<RhsType, Dim> rhs)
  {
    std::transform(rhs.begin(), rhs.end(), begin(), begin(), std::minus<>{});
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType>
  inline void Tuple<Type, Dim, Derived>::mul(RhsType factor)
  {
    std::transform(begin(), end(), begin(),
                   [factor](Type &el)
                   {
                     return el *= factor;
                   });
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline Derived<Type, Dim> Tuple<Type, Dim, Derived>::operator-() const
  {
    return Derived<Type, Dim>(*this).negate();
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  inline void Tuple<Type, Dim, Derived>::negate()
  {
    std::transform(begin(), end(), begin(), std::negate<>{});
  }
};
