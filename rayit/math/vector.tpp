namespace rt
{
  template <Arithmetic Type, size_t Dim>
  template <Arithmetic OtherType>
  Vector<Type, Dim> Vector<Type, Dim>::cross(Vector<OtherType, Dim> other) const
  {
    if (Dim != 3)
      throw std::runtime_error("Calculating cross product of vectors of dimension = " + Dim);

    return Vector<Type, Dim>{
      this->operator[](1) * other[2] - this->operator[](2) * other[1], // x' = y1*z2 - z1*y2
      this->operator[](2) * other[0] - this->operator[](0) * other[2], // y' = z1*x2 - x1*z2
      this->operator[](0) * other[1] - this->operator[](1) * other[0]  // z' = x1*y2 - y1*x2 
    };
  }
};
