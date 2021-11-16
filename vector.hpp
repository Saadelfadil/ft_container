/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:07:41 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/11/13 01:14:37 by sel-fadi         ###   ########.fr       */
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
			typedef VectorIterator<value_type const> const_iterator;
			typedef size_t size_type;
			// typedef ReverseIterator<iterator> reverse_iterator;
			// typedef ReverseIterator<const_iterator> const_reverse_iterator;

		private:
			value_type *m_data;
			size_type m_Size;
			size_type m_Capacity;
			allocator_type _alloc;
			Allocator my_allocator;
		
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
					my_allocator.destroy(&m_data[i]);
				if (m_data)
					my_allocator.deallocate(m_data, m_Size);
				this->m_Size = 0;
			}

			Vector&operator=(Vector const &obj)
			{
				this->p = obj.p;
				return *this;
			}

			void reserve (size_type n)
			{
			    value_type *newBlock = _alloc.allocate(n);
			    for (size_t i = 0; i < m_Size; i++)
			        _alloc.construct(&newBlock[i], m_data[i]);
			    for (size_type i = 0; i < m_Size; i++)
					_alloc.destroy(&m_data[i]);
				if (m_data)
					_alloc.deallocate(m_data, m_Size);
			    m_data = newBlock;
			    m_Capacity = n;
			}
			
			void resize (size_type n, value_type val = value_type())
			{
				size_type tmp;

				if (n < m_Size)
				{
					for (size_type i = n; i < m_Size; i++)
						_alloc.destroy(&m_data[i]);
				}
				else if (n > m_Size && n < m_Capacity)
				{
					for (size_type i = m_Size; i < n; i++)
						m_data[i] = val;
				}
				else if (n > m_Capacity)
				{
					tmp = m_Size;
					reserve(n);
					for (size_type i = tmp; i < n; i++)
						_alloc.construct(&m_data[i], val);
				}
				m_Size = n;
			}

			void push_back(const value_type &value)
			{
				if (m_Size == m_Capacity)
				{
					if (m_Capacity == 0)
						reserve(1);
					else
						reserve(m_Capacity * 2);
				}
				_alloc.construct(&m_data[m_Size], value);
				m_Size++;
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
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

			void assign (size_type n, const value_type& val)
			{
				m_data = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
			        _alloc.construct(&m_data[i], val);
				m_Capacity = m_Size = n;
			}

			void insert(T item)
			{
				if (m_Size >= m_Capacity)
					_alloc.allocate(m_Capacity * 2);
				_alloc.construct(&m_data[m_Size++], item);
			}

			bool empty() const
			{
				return m_Size == 0;
			}

			size_t size() const
			{
				return (this->m_Size);
			}

			size_t max_size() const
			{
				return (_alloc.max_size());
			}

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

			void clear()
			{
				for (size_t i = 0; i < m_Size; i++)
					m_data[i].~T();
				m_Size = 0;
			}

			bool operator==(Vector<T> const &obj) const
			{
				for (std::size_t i = 0; i < m_Size; i++)
					if (obj.array[i] != this->m_data[i])
						return false;
				return true;
			}

			const value_type&  operator[](size_type index) const
			{
				return (m_data[index]);
			}
			
			value_type&  operator[](size_type index)
			{
				return (m_data[index]);
			}

			reference at (size_type n)
			{
				if (n >= this->m_Size)
					throw std::out_of_range("Vector index out of range");
				return (this->m_data[n]);
			}

			const_reference at (size_type n) const
			{
				if (n >= this->m_Size)
					throw std::out_of_range("Vector index out of range");
				return (this->m_data[n]);
			}

			reference front()
			{
				return (this->m_data[0]);
			}

			const_reference front() const
			{
				return (this->m_data[0]);
			}

			reference back()
			{
				return (this->m_data[m_Size - 1]);
			}

			const_reference back() const
			{
				return (this->m_data[m_Size - 1]);
			}

			iterator begin()
			{
				return (iterator(m_data));
			}

			iterator end()
			{
				return (iterator(m_data + m_Size));
			}

			// iterator rbegin()
			// {
			// 	return (iterator(m_data + m_Size - 1));
			// }

			// iterator rend()
			// {
			// 	return (iterator(m_data - 1));
			// }

	};

}