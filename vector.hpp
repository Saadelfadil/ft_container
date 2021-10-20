#pragma once
#include <vector>
#include <iostream>

template <typename T>
class Vector
{
    public:
        Vector()
        {
            ReAlloc();
        }

        void pushBack(const T&value)
        {
            if (m_size >= m_Capacity)
                ReAlloc(m_Capacity + (m_Capacity / 2));
            m_data[m_Size] = value;
            m_Size++;
        }
        
        T&  operator[](size_t index)
        {
            return (m_data[index]);
        }

        size_t Size() const
        {
            return (this->m_Size);
        }

    private:
        void ReAlloc(size_t newCapacity)
        {
            T* newBlock = new T[newCapacity];
            if (newCapacity < m_Size)
                m_Size = newCapacity;
            for (size_t i = 0; i < m_Size; i++)
                newBlock[i] = m_data[i];
            delete [] m_data;
            m_data = newBlock;
            m_Capacity = newCapacity;
        }

        T* m_data = nullptr;

        size_t m_Size = 0;
        size_t m_Capacity = 0
};














































// iterator of vector

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
};