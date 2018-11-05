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


///////////----- Vector -----///////////
  template <typename T>
  Vector<T>::Vector() : Vector(min_sz) {}

  template <typename T>
  Vector<T>::Vector(size_type n) : sz{0}, max_sz{n < min_sz ? min_sz : n}, values{new value_type[max_sz]} {}

  template <typename T>
  Vector<T>::Vector(const std::initializer_list<value_type> list) : Vector(list.size())
    {
      for (const auto& value : list) { push_back(value); }
    }
    
  template <typename T>
  Vector<T>::Vector(const Vector& copy) : Vector(copy.max_sz)
    {
      for (size_t i {0}; i < copy.size(); ++i) { push_back(copy[i]); }
    }

  template <typename T>
  Vector<T>::~Vector() { delete[] values; }

  template <typename T>
  typename Vector<T>::size_type Vector<T>::size() const { return sz; }

  template <typename T>
  typename Vector<T>::size_type Vector<T>::max_size() const { return max_sz; }
    
  template <typename T>
  bool Vector<T>::empty() const { return sz == 0; }
    
  template <typename T>
  void Vector<T>::clear() { sz = 0; }
    
  template <typename T>
  void Vector<T>::reserve(size_type n)
    {
      if (n < min_sz) n = min_sz;
      if (n <= max_sz) return;
      new_buf(n);
    }

  template <typename T>
  void Vector<T>::shrink_to_fit() { new_buf(sz); }
    
  template <typename T>
  void Vector<T>::push_back(value_type x)
    {
      if (sz >= max_sz) reserve(max_sz+1);
      values[sz++] = x;
    }
    
  template <typename T>
  void Vector<T>::pop_back()
    {
      if (sz == 0)
        throw std::runtime_error("Pop_back - Vector is empty!");
      --sz;
    }
    
  template <typename T>
  Vector<T> Vector<T>::operator= (const Vector& v)
    {
      delete[] values;
      sz = 0;
      max_sz = min_sz;
      values = nullptr;
      values = new value_type[v.max_size()];
      max_sz = v.max_size();
      sz = v.size();
      std::copy(v.values, v.values + v.size(), values);
      return *this;
    }
    
  template <typename T>
  typename Vector<T>::reference Vector<T>::operator[](size_type index)
    {
      if (index >= sz)
        throw std::runtime_error("Index is outside our Vector!");
      return values[index];
    }
    
  template <typename T>
  typename Vector<T>::const_reference Vector<T>::operator[](size_type index) const
    {
      if (index >= sz)
        throw std::runtime_error("Index is outside our Vector!");
      return values[index];
    }
    
  template <typename T>
  bool Vector<T>::operator<(const Vector& rop)
    {
      return this < rop;
    }
    
  template <typename T>
  typename Vector<T>::iterator Vector<T>::begin() { return Iterator(values); }
    
  template <typename T>
  typename Vector<T>::iterator Vector<T>::end() { return Iterator(values+sz); }

  template <typename T>
  typename Vector<T>::const_iterator Vector<T>::begin() const { return ConstIterator(values); }
    
  template <typename T>
  typename Vector<T>::const_iterator Vector<T>::end() const { return ConstIterator(values+sz); }

  ///////////*----- Insert, Erase from VO -----*///////////
  template <typename T>
  typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const_reference val)
    {
      auto diff = pos - begin();
      if (diff < 0 || static_cast<size_type>(diff) > sz)
        throw std::runtime_error("Error insert! Iterator is out of bounds");
      size_type current {static_cast<size_type>(diff)};
      if (sz >= max_sz)
        reserve(max_sz*2);
      for (size_t i {sz}; i-->current;)
        values[i+1] = values[i];
      values[current] = val;
      ++sz;
      return iterator{values+current};
    }
    
  template <typename T>
  typename Vector<T>::iterator Vector<T>::erase(const_iterator pos)
    {
      auto diff = pos - begin();
      if (diff < 0 || static_cast<size_type>(diff) >= sz)
        throw std::runtime_error("Error Erase! Iterator is out of bounds");
      size_type current{static_cast<size_type>(diff)};
      for (size_type i{current}; i < sz-1; ++i)
        values[i] = values[i+1];
      --sz;
      return iterator{values+current};
    }

    
///////////----- Iterator -----///////////
  template <typename T>
  Vector<T>::Iterator::Iterator() : ptr{nullptr} {}

  template <typename T>
  Vector<T>::Iterator::Iterator(pointer Ptr) : ptr{Ptr} {}

  template <typename T>
  typename Vector<T>::Iterator::reference Vector<T>::Iterator::operator*() { return *ptr; }

  template <typename T>
  typename Vector<T>::Iterator::pointer Vector<T>::Iterator::operator->() { return ptr; }

  template <typename T>
  bool Vector<T>::Iterator::operator==(const iterator& rop) const { return ptr == rop.ptr; }

  template <typename T>
  bool Vector<T>::Iterator::operator!=(const iterator& rop) const { return ptr != rop.ptr; }

  template <typename T>
  bool Vector<T>::Iterator::operator==(const const_iterator& rop) const { return static_cast<const_iterator>(*this) == rop; }

  template <typename T>
  bool Vector<T>::Iterator::operator!=(const const_iterator& rop) const { return static_cast<const_iterator>(*this) != rop; }

  template <typename T>
  typename Vector<T>::iterator& Vector<T>::Iterator::operator++()
    {
      ++ptr;
      return *this;
    }

  template <typename T>
  typename Vector<T>::iterator Vector<T>::Iterator::operator++(int)
    {
      Iterator temp(*this);
      operator++();
      return temp;
    }

  template <typename T>
  typename Vector<T>::Iterator::difference_type Vector<T>::Iterator::operator-(const Iterator& rop) { return ptr - rop.ptr; }

  template <typename T>
  Vector<T>::Iterator::operator const_iterator() const { return ConstIterator{ptr}; }


///////////----- ConstIterator -----///////////
  template <typename T>
  Vector<T>::ConstIterator::ConstIterator() : ptr{nullptr} {}

  template <typename T>
  Vector<T>::ConstIterator::ConstIterator(pointer Ptr) : ptr{Ptr} {}

  template <typename T>
  typename Vector<T>::ConstIterator::reference Vector<T>::ConstIterator::operator*() { return *ptr; }

  template <typename T>
  typename Vector<T>::ConstIterator::pointer Vector<T>::ConstIterator::operator->() { return ptr; }

  template <typename T>
  bool Vector<T>::ConstIterator::operator==(const const_iterator& rop) const { return ptr == rop.ptr; }

  template <typename T>
  bool Vector<T>::ConstIterator::operator!=(const const_iterator& rop) const { return ptr != rop.ptr; }

  template <typename T>
  typename Vector<T>::const_iterator& Vector<T>::ConstIterator::operator++()
    {
    ++ptr;
    return *this;
    }

  template <typename T>
  typename Vector<T>::const_iterator Vector<T>::ConstIterator::operator++(int)
    {
    ConstIterator temp(*this);
    operator++();
    return temp;
    }

  template <typename T>
  typename Vector<T>::ConstIterator::difference_type Vector<T>::ConstIterator::operator-(const ConstIterator& rop) { return ptr - rop.ptr; }

    
    
#endif /* vector_h */
