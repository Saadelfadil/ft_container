#pragma once
#include <iostream>
#include <string>

#include <vector>
template <typename T, class Allocator = std::allocator<T> >
class Vector
{

}


template <typename T>
class VectorIterator
{
    public:
        typedef category iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type *pointer;
        typedef value_type &reference;
    public:
        
}