/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:07:41 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/11/13 01:04:50 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include "iterator_traits.hpp"

namespace ft {
	
	template <typename T>
	class VectorIterator : public ft::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T value_type;
			typedef value_type* pointer;
			typedef value_type const * const_pointer;
			typedef value_type& reference;
			typedef value_type const & const_reference;
			typedef std::ptrdiff_t difference_type;
		protected:
			pointer p;
		public:
			VectorIterator() {}
			VectorIterator(pointer ptr) : p(ptr) {}
			// VectorIterator(pointer const &obj) : p(obj) {}
			virtual ~VectorIterator() {}

			VectorIterator &operator=(VectorIterator<T> const &obj)
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
				p++;
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
				p--;
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
				return *(p + index);
			}

			const_reference operator[](int index) const
			{
				return *(p + index);
			}

			pointer operator->()
			{
				return p;
			}

			const_pointer operator->() const
			{
				return p;
			}

			reference operator*()
			{
				return *p;
			}
			
			const_pointer operator*() const
			{
				return *p;
			}

			difference_type operator-(VectorIterator const &obj) const
			{
				return (this->p - obj.p);
			}

			bool operator==(VectorIterator const &obj) const {
				return (this->p == obj.p);
			}

			bool operator!=(VectorIterator const &obj) const {
				return (this->p != obj.p);
			}

			bool operator<(VectorIterator const &obj) const {
				return (this->p < obj.p);
			}

			bool operator<=(VectorIterator const &obj) const {
				return (this->p <= obj.p);
			}

			bool operator>(VectorIterator const &obj) const {
				return (this->p > obj.p);
			}

			bool operator>=(VectorIterator const &obj) const {
				return (this->p >= obj.p);
			}
	};

	template <typename T, class Allocator = std::allocator<T> >
	class Vector
	{
		public:
			typedef T value_type;
			typedef value_type* pointer;
			typedef value_type const * const_pointer;
			typedef value_type& reference;
			typedef value_type const & const_reference;
			typedef std::ptrdiff_t difference_type;
			typedef VectorIterator<value_type> iterator;
			typedef Allocator allocator_type;
			typedef size_t size_type;
			// typedef typename VectorIterator<value_type> iterator;
			typedef VectorIterator<value_type const> const_iterator;
			// typedef ReverseIterator<iterator> reverse_iterator;
			// typedef ReverseIterator<const_iterator> const_reverse_iterator;
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
			value_type *m_data;
			size_type m_Size;
			size_type m_Capacity;
			allocator_type _alloc;
		public:
			explicit Vector (const allocator_type& alloc = allocator_type()) : m_data(nullptr), m_Size(0), m_Capacity(0), _alloc(alloc)
			{
			}
			
			explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				m_data = _alloc.allocate(n);
				if (n < m_Size)
					m_Size = n;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&m_data[i], val);
				m_Capacity = n;
				m_Size = n;
			}

			template <class iterator>
			Vector (iterator first, iterator last, const allocator_type& alloc = allocator_type())
			{
				size_type len = last - first;
				m_data = _alloc.allocate(len);
				size_type i = 0;
				while (first != last)
				{
					_alloc.construct(&m_data[i], *first);
					first++;
					i++;
				}
				m_Capacity = m_Size = i;
 	 		}
			
			Vector (const Vector &obj)
			{
				this->p = obj.p;
			}

			virtual ~Vector()
			{
				for (size_type i = 0; i < m_Size; i++)
					this->m_data[i].value_type::~value_type();
				this->size = 0;
				if (m_data)
					Allocator.destroy(m_data);
				// Allocator.deallocate(m_data);
					
				// destroy_memory(m_data);
				// deallocate_memory(m_data, m_Capacity);
			}
			
			// Vector(size_t size, size_t capacity) : m_Size(size), m_Capacity(capacity)
			// {
			// 	// ReAlloc(2);
			// 	allocate_memory(2);
			// }
			// Vector() : m_data(nullptr), m_Size(0), m_Capacity(0)
			// {
			// 	// ReAlloc(2);
			// 	allocate_memory(2);
			// }


			Vector&operator=(Vector const &obj)
			{
				this->p = obj.p;
				return *this;
			}


			void push_back(const T&value)
			{
				if (m_Size == 0)
					allocate_memory(1);
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

			size_t empty() const
			{
				return m_Size == 0;
			}

			size_t size() const
			{
				return (this->m_Size);
			}

			// size_t max_size() const
			// {
			// 	return (Allocator.max_size());
			// }

			size_t capacity() const
			{
				return (this->m_Capacity);
			}

			void pop_back()
			{
				if (m_Size > 0)
				{
					m_Size--;
					m_data[m_Size].~T();
				}
			}
			
			// void swap()
			// {
				
			// }

			void clear()
			{
				for (size_t i = 0; i < m_Size; i++)
					m_data[i].~T();
				m_Size = 0;
			}

			// T&  operator=(Vector<T> const &obj)
			// {
			// 	*this = obj;
			// }

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

			iterator begin()
			{
				return (iterator(m_data));
			}

			// iterator rbegin()
			// {
			// 	return (iterator(m_data + m_Size - 1));
			// }

			iterator end()
			{
				return (iterator(m_data + m_Size));
			}

			// iterator rend()
			// {
			// 	return (iterator(m_data - 1));
			// }

	};

}