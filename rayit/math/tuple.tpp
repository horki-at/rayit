namespace rt
{
  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  void Tuple<Type, Dim, Derived>::swap(Tuple &other) noexcept
  {
    size_t const tuple_size = sizeof(Tuple<Type, Dim, Derived>);
    char buffer[tuple_size];    // temporary buffer to copy other into

    memcpy(buffer, &other, tuple_size);
    memcpy(reinterpret_cast<void *>(&other), this, tuple_size);
    memcpy(reinterpret_cast<void *>(*this), &other, tuple_size);
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType>
  Derived<Type, Dim> &Tuple<Type, Dim, Derived>::operator/=(RhsType factor)
  {
    Derived<Type, Dim> cpy(*this);
    cpy.div(factor);
    swap(*this, cpy);
    return static_cast<Derived<Type, Dim> &>(*this);
  }

  template <Arithmetic Type, size_t Dim, template <Arithmetic, size_t> class Derived>
  template <Arithmetic RhsType>
  void Tuple<Type, Dim, Derived>::div(RhsType factor)
  {
    if (not factor)             // factor is zero => division by zero 
      throw std::invalid_argument("division of a tuple by 0");
    
    std::transform(begin(), end(), begin(),
                   [factor](Type &el)
                   {
                     return el /= factor;
                   });
  }
};
