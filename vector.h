#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector{
  public:
    class Iterator;
    class ConstIterator;
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
    size_type sz;
    size_type max_sz;
    pointer values;
  public:
    Vector() : sz{0}, max_sz{0}, values{new value_type[0]} {};

    Vector(const size_type n) : sz{0}, max_sz{n}, values{new value_type[n]} {};

    Vector(std::initializer_list<value_type> list) : Vector(list.size()) {
      size_type i{0};

      for(const auto& value : list)
        values[i++] = value;

      sz = i;
    }

    Vector(const Vector& v) : Vector(v.sz) {
      for(size_type i{0}; i < v.sz; ++i)
        values[i] = v.values[i];

      sz = v.sz;
    }

    ~Vector() {delete[] values;}

    Vector& operator=(Vector v) {
      std::swap(sz, v.sz);
      std::swap(max_sz, v.max_sz);
      std::swap(values, v.values);

      return *this;
    }

    inline size_type size() const {
      return sz;
    }

    bool empty() const {
      if(sz == 0)
        return true;

      return false;
    }

    void clear() {
      if(this -> empty())
        return;

      sz = 0;
    }

    void reserve(size_type n) {
      if(max_sz >= n)
        return;

      value_type* new_values{new value_type[n]};

      for(size_type i{0}; i < sz; ++i)
        new_values[i] = values[i];

      delete[] values;
      values = new_values;

      max_sz = n;
    }

    inline void shrink_to_fit() {
      max_sz = sz;
    }

    void push_back(value_type x) {
      if(max_sz <= sz)
        reserve(2 * (sz + 1));

      values[sz] = x;
      ++sz;
    }

    void pop_back() {
      if(this -> empty())
        throw std::runtime_error("Vector is empty!");

      --sz;
    }

    value_type& operator[](size_t index) {
      if(index < 0 || index >= sz)
        throw std::runtime_error("Invalid index!");

      return values[index];
    }

    const value_type& operator[](size_t index) const {
      if(index < 0 || index >= sz)
        throw std::runtime_error("Invalid index!");

      return values[index];
    }

    inline size_type capacity() const {
      return max_sz;
    }

    iterator begin() {const iterator i{values}; return i;}

    iterator end() {const iterator i{values + sz}; return i;}

    const_iterator begin() const {const const_iterator i{values}; return i;}

    const_iterator end() const {const const_iterator i{values + sz}; return i;}

    iterator insert(const_iterator pos, const_reference val) {
      auto diff = pos - begin();

      if(diff < 0 || static_cast<size_type>(diff) > sz)
        throw std::runtime_error("Iterator out of bounds!");

      size_type current{static_cast<size_type>(diff)};

      if(sz >= max_sz)
        reserve(2 * max_sz + 1);

      for(auto i{sz}; i-- > current;)
        values[i + 1] = values[i];

      values[current] = val;

      ++sz;

      return iterator{values + current};
    }


    iterator erase(const_iterator pos) {
      auto diff = pos - begin();

      if(diff < 0 || static_cast<size_type>(diff) >= sz)
        throw std::runtime_error("Iterator out of bounds!");

      size_type current{static_cast<size_type>(diff)};

      for(auto i{current}; i < sz - 1; ++i)
        values[i] = values[i + 1];

      --sz;

      return iterator{values + current};
    }


    friend std::ostream& operator<<(std::ostream& o, const Vector& v) {
      o << '[';
      bool first{true};

      for(size_type i{0}; i < v.sz;) {
        if(first)
          first = false;
        else
          o << ", ";

        o << v.values[i++];
      }

      return o << ']';
    }

  class Iterator {
    public:
      using value_type = Vector::value_type;
      using reference = Vector::reference;
      using pointer = Vector::pointer;
      using difference_type = Vector::difference_type;
      using iterator_category = std::forward_iterator_tag;
    private:
      pointer ptr;
    public:
      Iterator() : ptr{nullptr} {};
      Iterator(pointer ptr) : ptr{ptr} {};
      reference operator*() const {return *ptr;};
      pointer operator->() const {return ptr;};
      bool operator==(const const_iterator& rit) const {const const_iterator& lit{ptr}; if(lit == rit) return true; return false;}
      bool operator!=(const const_iterator& rit) const {const const_iterator& lit{ptr}; if(lit != rit) return true; return false;}
      iterator& operator++() {++ptr; return *this;}
      iterator operator++(int) {pointer ptr1{ptr}; ++ptr; return ptr1;}
      difference_type operator-(const const_iterator& it) const {const const_iterator& lit{ptr}; return lit - it;}
      operator const_iterator() const {return static_cast<const_iterator>(ptr);}
  };

  class ConstIterator {
    public:
      using value_type = Vector::value_type;
      using reference = Vector::const_reference;
      using pointer = Vector::const_pointer;
      using difference_type = Vector::difference_type;
      using iterator_category = std::forward_iterator_tag;
    private:
      pointer ptr;
    public:
      ConstIterator() {};
      ConstIterator(pointer ptr) : ptr{ptr} {};
      reference operator*() const {return *ptr;}
      pointer operator->() const {return ptr;}
      bool operator==(const const_iterator& it) const {if(ptr == it.ptr) return true; return false;}
      bool operator!=(const const_iterator& it) const {if(ptr != it.ptr) return true; return false;}
      const_iterator& operator++() {++ptr; return *this;}
      const_iterator operator++(int) {pointer ptr1{ptr}; ++ptr; return ptr1;}
      difference_type operator-(const const_iterator& it) const {return ptr - it.ptr;}
  };
};

#endif
