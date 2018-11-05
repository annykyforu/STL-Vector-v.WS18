//  vector.h
//  Vector_ws18
//
//  Created by annykyforu on 03.10.18.
//  Copyright © 2018 PRG_2. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <stdexcept>

static constexpr size_t min_sz{1};

template <typename T>
class Vector;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec)
{
  if (vec.size() == 0)
  {
    os << "Our Vector is empty! Nothing to display.";
  } else {
    os << "[";
    for (size_t i {0}; i < vec.size(); ++i)
    {
      os << vec[i];
      if (i < vec.size()-1) { os << "," << '\n'; }
    }
    os << "]";
  }
  return os;
}

template <typename T>
class Vector
{
public:
  class ConstIterator;
  class Iterator;
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = Vector::Iterator;
  using const_iterator = Vector::ConstIterator;
private:
  size_type sz;  //actual qty of elements in Vector
  size_type max_sz;  //max qty of elements in Vector
  pointer values;
  void new_buf(size_type size)
    {
      if (size == max_sz) return;
      if (size < sz)
        throw std::runtime_error("New capacity is smaller than current size!");
      pointer buf = new value_type[size];
      for (size_type i{0}; i < this->sz; ++i)
        {
          buf[i] = values[i];
        }
      delete[] values;
      values = buf;
      max_sz = size;
    }
public:
  Vector();
  Vector(size_type);
  Vector(const std::initializer_list<value_type>);
  Vector(const Vector&);
  ~Vector();

  size_type size() const;
  size_type max_size() const;
  bool empty() const;
  void clear();
  void reserve(size_type);
  void shrink_to_fit();
  void push_back(value_type);
  void pop_back();
  Vector operator= (const Vector&);
  reference operator[](size_type);
  const_reference operator[](size_type) const;
  bool operator<(const Vector&);
    
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  ///////////*----- Insert, Erase from VO -----*///////////
  iterator insert(const_iterator, const_reference);
  iterator erase(const_iterator);
  
  friend std::ostream& operator<< <>(std::ostream&, const Vector<T>&);
    
  ///////////*----- Iterator -----*///////////
  class Iterator
  {
  public:
    using value_type = Vector::value_type;
    using reference = Vector::reference;
    using pointer = Vector::pointer;
    using difference_type = Vector::difference_type;
    using iterator_category = std::forward_iterator_tag;
  private:
    pointer ptr;
  public:
    Iterator();
    Iterator(pointer);
    reference operator*();
    pointer operator->();
    bool operator==(const iterator&) const;
    bool operator!=(const iterator&) const;
    bool operator==(const const_iterator&) const;
    bool operator!=(const const_iterator&) const;
    iterator& operator++();
    iterator operator++(int);
    difference_type operator-(const Iterator&);
    operator const_iterator() const;
  };
    
  ///////////*----- ConstIterator -----*///////////
  class ConstIterator
  {
  public:
    using value_type = Vector::value_type;
    using reference = Vector::const_reference;
    using pointer = Vector::const_pointer;
    using difference_type = Vector::difference_type;
    using iterator_category = std::forward_iterator_tag;
  private:
    pointer ptr;
  public:
    ConstIterator();
    ConstIterator(pointer);
    reference operator*();
    pointer operator->();
    bool operator==(const const_iterator&) const;
    bool operator!=(const const_iterator& rop) const;
    const_iterator& operator++();
    const_iterator operator++(int);
    difference_type operator-(const ConstIterator&);
  };
};    
    
#endif /* vector_h */
