//  vector.h
//  Vector_ws18
//
//  Created by annykyforu on 03.10.18.
//  Copyright © 2018 PRG_2. All rights reserved.
//

#include"vector.h"

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
bool Vector<T>::operator<(const Vector& rop) { return this < rop; }

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
