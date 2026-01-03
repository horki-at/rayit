namespace rt
{
  template <Arithmetic Type, size_t Dim>
  template <Arithmetic OtherType>
  inline Type Vector<Type, Dim>::dot(Vector<OtherType, Dim> other) const
  {
    return std::inner_product(this->begin(), this->end(), other.begin(), Type{});
  }

  template <Arithmetic Type, size_t Dim>
  inline VectorLengthType<Type>::type Vector<Type, Dim>::length() const
  {                             // |this| = sqrt(this dot this)
    return std::sqrt(dot(*this));
  }

  template <Arithmetic Type, size_t Dim>
  inline void Vector<Type, Dim>::norm()
  {
    this->operator*=(1 / length());
  }

  template <Arithmetic Type, size_t Dim>
  inline Vector<Type, Dim> Vector<Type, Dim>::unit() const
  {
    return Vector<Type, Dim>(*this).norm();
  }
};
