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
	
	template <typename> struct is_integral{static const bool type = false;};
	template <> struct is_integral<bool>{static const bool type = true;};
	template <> struct is_integral<char>{static const char type = true;};
	template <> struct is_integral<char16_t>{static const char16_t type = true;};
	template <> struct is_integral<char32_t>{static const char32_t type = true;};
	template <> struct is_integral<wchar_t>{static const wchar_t type = true;};
	template <> struct is_integral<signed char>{static const signed char type = true;};
	template <> struct is_integral<short int>{static const short int type = true;};
	template <> struct is_integral<int>{static const int type = true;};
	template <> struct is_integral<long int>{static const long int type = true;};
	template <> struct is_integral<long long int>{static const long long int type = true;};
	template <> struct is_integral<unsigned char>{static const unsigned char type = true;};
	template <> struct is_integral<unsigned short int>{static const unsigned short int type = true;};
	template <> struct is_integral<unsigned int>{static const unsigned int type = true;};
	template <> struct is_integral<unsigned long int>{static const unsigned long int type = true;};
	template <> struct is_integral<unsigned long long int>{static const unsigned long long int type = true;};


	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

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
			virtual ~VectorIterator() {}
			VectorIterator &operator=(VectorIterator<value_type> const &obj)
			{
				this->p = obj.p;
				return (*this);
			}

			VectorIterator &operator+=(int value)
			{
				this->p += value;
				return (*this);
			}

			VectorIterator &operator-=(int value)
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
			Vector (iterator first, iterator last, const allocator_type& alloc = allocator_type(), typename std::enable_if<!std::is_integral<iterator>::value, iterator >::type* dummy = 0)
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

			template <class iterator>
			void assign (iterator first, iterator last, typename enable_if<!std::is_integral<iterator>::value, iterator >::type* dummy = 0)
			{
				difference_type len = last - first;
				if (len > this->m_Capacity)
					reserve(len);
				else
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
				if (n > this->m_Capacity)
					reserve(n);
				else
					m_data = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
			        _alloc.construct(&m_data[i], val);
				m_Capacity = m_Size = n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!std::is_integral<InputIterator>::value, InputIterator >::type* dummy = 0)
			{
				difference_type index = position - begin();
				difference_type len = last - first;
				if (this->m_Size == 0)
					reserve(len);
				else if (this->m_Size + len > m_Capacity)
				{
					if (len > m_Size)
						reserve(m_Size + len);
					else
						reserve(m_Capacity * 2);
				}
				for (difference_type i = m_Size - 1; i >= index; i--)
					_alloc.construct(&m_data[i + len], m_data[i]);
				for (size_type i = 0; i < len; i++)
				{
					_alloc.construct(&m_data[index++], *first);
					first++;
				}
				this->m_Size += len;
			}

			iterator insert (iterator position, const value_type& val)
			{
				difference_type index = position - begin();
                if (this->m_Size == 0)
					reserve(1);
                else if (this->m_Size + 1 > this->m_Capacity)
					reserve(this->m_Capacity * 2);
                for (difference_type i = this->m_Size - 1; i >= index; i--)
					_alloc.construct(&m_data[i + 1], m_data[i]);
                _alloc.construct(&m_data[index], val);
                this->m_Size++;
                return (iterator(this->m_data + index));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type index = position - begin();
                if (this->m_Size == 0)
					reserve(n);
				else if (this->m_Size + n > this->m_Capacity)
				{
					if (this->m_Size < n)
						reserve(this->m_Size + n);
					else
						reserve(this->m_Capacity * 2);
				}
				for (difference_type i = this->m_Size - 1; i >= index; i--)
					_alloc.construct(&m_data[i + n], m_data[i]);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&m_data[index++], val);
				this->m_Size += n;
			}

			iterator erase(iterator position)
			{
				difference_type index = position - begin();
				_alloc.destroy(&m_data[index]);
                for (difference_type i = index; i < m_Size; i++)
					_alloc.construct(&m_data[i], m_data[i + 1]);
                this->m_Size--;
                return (iterator(this->m_data + index));
			}

			iterator erase (iterator first, iterator last)
			{
				difference_type index = first - begin();
				difference_type len = last - first;
                for (size_type i = index; i < len; i++)
                    _alloc.destroy(&this->m_data[i]);
                this->m_Size -= len;
                for (size_type i = index; i < this->m_Size; i++)
					_alloc.construct(&m_data[i], m_data[len++]);
                return (iterator(this->m_data + index));
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
				if (m_Size == 0 || m_Capacity == 0)
					return;
				_alloc.destroy(&m_data[m_Size]);
				m_Size--;
			}

			void clear()
			{
				for (size_t i = 0; i < m_Size; i++)
					_alloc.destroy(m_data[i]);
				m_Size = 0;
			}

			// void swap (Vector &x)
			// {
			// 	clear();
			// 	reserve(x.size());
			// 	for (size_type i = 0; i < x.size(); i++)
			//         _alloc.construct(&m_data[i], x[i]);
			// }

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