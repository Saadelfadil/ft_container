#pragma once
#include <iostream>
#include <string>

// #include <vector>

template <typename T, class Allocator = std::allocator<T> >
class Vector
{
    private:
        std::allocator<T> myallo;
        // void ReAlloc(size_t newCapacity)
        // {
        //     T* newBlock = new T[newCapacity];
        //     if (newCapacity < m_Size)
        //         m_Size = newCapacity;
        //     for (size_t i = 0; i < m_Size; i++)
        //         newBlock[i] = m_data[i];
        //     delete [] m_data;
        //     m_data = newBlock;
        //     m_Capacity = newCapacity;
        // }

        T* allocate_memory( std::size_t n)
        {
            T* newBlock = myallo.allocate(n);
            if (n < m_Size)
                m_Size = n;
            for (size_t i = 0; i < m_Size; i++)
                newBlock[i] = m_data[i];
            // delete [] m_data;
            m_data = newBlock;
            m_Capacity = n;
            return m_data;
        }

        void deallocate_memory(T* p, std::size_t n )
        {
            myallo.deallocate(p, n);
        }

        void destroy_memory(T* p)
        {
            p->~T();
        }

    private:
        T* m_data; 
        size_t m_Size;
        size_t m_Capacity;
    public:
        Vector() : m_data(nullptr), m_Size(0), m_Capacity(0)
        {
            // ReAlloc(2);
            allocate_memory(2);
        }

        ~Vector()
        {
            deallocate_memory(m_data, m_Capacity);
            destroy_memory(m_data);
            // delete[] m_data;
        }

        void PushBack(const T&value)
        {
            if (m_Size >= m_Capacity)
                allocate_memory(m_Capacity * 2);
            m_data[m_Size] = value;
            m_Size++;
        }

        void insert(T item)
        {
            if (m_Size >= m_Capacity)
                allocate_memory(m_Capacity * 2);
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

        T&  operator=(Vector<T> const &obj)
        {
            *this = obj;
        }

        bool operator==(Vector<T> const &obj) const
        {
            for (std::size_t i = 0; i < m_Size; i++)
                if (obj.array[i] != this->m_data[i])
                    return false;
            return true;
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