#pragma once
#include <iostream>
#include <string>
#include <vector>


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
            for (size_t i = 0; i < m_Size; i++)
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
            destroy_memory(m_data);
            deallocate_memory(m_data, m_Capacity);
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

template <typename T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
    protected:
        pointer m_ptr;
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef value_type const * const_pointer;
        typedef value_type& reference;
        typedef value_type const & const_reference;
        typedef std::ptrdiff_t difference_type;

    public:
        VectorIterator() : p(nullptr) {}
        VectorIterator(pointer ptr) : m_ptr(ptr) {}
        VectorIterator(pointer const &obj) : p(obj.p) {}
        virtual ~VectorIterator() {}


        VectorIterator &operator=(VectorIterator const &obj)
        {
            this->p = obj.p;
            return (*this);
        }

        VectorIterator &operator+=(int value) const
        {
            this->p += value;
            return (*this);
        }

        VectorIterator &operator-=(int value) const
        {
            this->p -= value;
            return (*this);
        }

        VectorIterator &operator+(int value) const
        {
            VectorIterator it(*this);
            return (it += value);
        }

        VectorIterator &operator-(int value) const
        {
            VectorIterator it(*this);
            return (it -= value);
        }

        VectorIterator operator++()
        {
            m_ptr++;
            return *this;
        }

        VectorIterator operator++(int)
        {
            VectorIterator it(*this);
            ++(*this);
            return it;
        }

        VectorIterator operator--()
        {
            m_ptr--;
            return *this;
        }

        VectorIterator operator--(int)
        {
            VectorIterator it(*this);
            --(*this);
            return it;
        }

        reference operator[](int index)
        {
            return *(m_ptr + index);
        }

        const_reference operator[](int index) const
        {
            return *(m_ptr + index);
        }

        pointer operator->()
        {
            return m_ptr;
        }

        const_pointer operator->() const
        {
            return m_ptr;
        }

        pointer operator*()
        {
            return *m_ptr;
        }
        
        const_pointer operator*() const
        {
            return *m_ptr;
        }

        difference_type operator-(VectorIterator const &obj) const
        {
            return (this->p - obj.p);
        }

        bool operator==(VectorIterator const &obj) const {
		    return (this->m_ptr == obj.m_ptr);
        }

        bool operator!=(VectorIterator const &obj) const {
            return (this->m_ptr != obj.m_ptr);
        }

        bool operator<(VectorIterator const &obj) const {
            return (this->m_ptr < obj.m_ptr);
        }

        bool operator<=(VectorIterator const &obj) const {
            return (this->m_ptr <= obj.m_ptr);
        }

        bool operator>(VectorIterator const &obj) const {
            return (this->m_ptr > obj.m_ptr);
        }

        bool operator>=(VectorIterator const &obj) const {
            return (this->m_ptr >= obj.m_ptr);
        }
};