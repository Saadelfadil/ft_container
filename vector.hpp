#pragma once
#include <vector>
#include <iostream>

template <typename Vector>
class VectorIterator
{
    private:
        PointerType m_Ptr;
    public:
        using ValueType = typename Vector::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;
    public:
        VectorIterator(PointerType ptr) : m_Ptr(ptr) {}


        VectorIterator operator++()
        {
            m_Ptr++;
            return *this;
        }

        VectorIterator operator++(int)
        {
            VectorIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        VectorIterator operator--()
        {
            m_Ptr--;
            return *this;
        }

        VectorIterator operator--(int)
        {
            VectorIterator iterator = *this;
            --(*this);
            return iterator;
        }

        ReferenceType operator[](int index)
        {
            return *(m_Ptr + index);
        }

        PointerType operator->()
        {
            return m_Ptr;
        }

        PointerType operator*()
        {
            return *m_Ptr;
        }

        bool operator==(const VectorIterator &other) const
        {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const VectorIterator &other) const
        {
            return !(m_Ptr == other.m_Ptr);
        }
}