#pragma once
#include <iostream>
#include <string>

// #include <vector>

template <typename T>
class Vector
{
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
    private:
        T* m_data; 
        size_t m_Size;
        size_t m_Capacity;
    public:
        Vector() : m_data(nullptr), m_Size(0), m_Capacity(0)
        {
            ReAlloc(2);
        }

        ~Vector()
        {
            delete[] m_data;
        }
		
        void PushBack(const T&value)
        {
            if (m_Size >= m_Capacity)
                ReAlloc(m_Capacity * 2);
            m_data[m_Size] = value;
            m_Size++;
        }

        void insert(T item)
        {
            if (m_Size >= m_Capacity)
                ReAlloc(m_Capacity * 2);
            m_data[m_Size++] = item;
        }

        size_t isEmpty() const
        {
            return m_Size == 0;
        }

        size_t Size() const
        {
            return (this->m_Size);
        }

        void popBack()
        {
            if (m_Size > 0)
            {
                m_Size--;
                m_data[m_Size].~T();
            }
        }

        void Clear()
        {
            for (size_t i = 0; i < m_Size; i++)
                m_data[i].~T();
            m_Size = 0;
        }

        T&  operator=(T const &obj)
        {
            *this = obj;
        }

        const T&  operator[](size_t index) const
        {
            return (m_data[index]);
        }
        
        T&  operator[](size_t index)
        {
            return (m_data[index]);
        }

};










// iterator of vector

// template <typename Vector>
// class VectorIterator
// {
//     private:
//         PointerType m_Ptr;
        
//     public:
//         using ValueType = typename Vector::ValueType;
//         using PointerType = ValueType*;
//         using ReferenceType = ValueType&;

//     public:

//         VectorIterator(PointerType ptr) : m_Ptr(ptr) {}

//         VectorIterator operator++()
//         {
//             m_Ptr++;
//             return *this;
//         }

//         VectorIterator operator++(int)
//         {
//             VectorIterator iterator = *this;
//             ++(*this);
//             return iterator;
//         }

//         VectorIterator operator--()
//         {
//             m_Ptr--;
//             return *this;
//         }

//         VectorIterator operator--(int)
//         {
//             VectorIterator iterator = *this; 
//             --(*this);
//             return iterator;
//         }

//         ReferenceType operator[](int index)
//         {
//             return *(m_Ptr + index);
//         }

//         PointerType operator->()
//         {
//             return m_Ptr;
//         }

//         PointerType operator*()
//         {
//             return *m_Ptr;
//         }

//         bool operator==(const VectorIterator &other) const
//         {
//             return m_Ptr == other.m_Ptr;
//         }

//         bool operator!=(const VectorIterator &other) const
//         {
//             return !(m_Ptr == other.m_Ptr);
//         }
// };