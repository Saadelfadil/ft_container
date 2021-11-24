/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:43:04 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/11/24 12:16:52 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include "iterator_traits.hpp"

namespace ft {
	
	template <class Iterator>
	class reverse_iterator {
		public:
			typedef Iterator iterator_type;
			typedef typename  iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename  iterator_traits<Iterator>::value_type value_type;
			typedef typename  iterator_traits<Iterator>::difference_type difference_type;
			typedef typename  iterator_traits<Iterator>::pointer pointer;
			typedef typename  iterator_traits<Iterator>::pointer const *const_pointer;
			typedef typename  iterator_traits<Iterator>::reference reference;
			typedef typename  iterator_traits<Iterator>::reference const &const_reference;
		protected:
			iterator_type _iterator;
		public:

		reverse_iterator() : _iterator(0) {};

		explicit reverse_iterator (iterator_type it)
		{
			iterator_type tmp = it;
			--tmp;
			_iterator = tmp;
		}
		
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _iterator(rev_it.base()) {};
		
		virtual reverse_iterator();

		iterator_type base() const
		{
			return (this->_iterator);
		}

		reference operator*()
		{
			return *p;
		}
		
		const_pointer operator*() const
		{
			return *p;
		}

		reverse_iterator &operator+(int value) const
		{
			reverse_iterator it(*this);
			return (it += value);
		}

		reverse_iterator operator++()
		{
			p++;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator it(*this);
			++(*this);
			return it;
		}

		reverse_iterator &operator+=(int value)
		{
			this->p += value;
			return (*this);
		}

		reverse_iterator &operator-(int value) const
		{
			reverse_iterator it(*this);
			return (it -= value);
		}

		reverse_iterator operator--()
		{
			p--;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator it(*this);
			--(*this);
			return it;
		}

		reverse_iterator &operator-=(int value)
		{
			this->p -= value;
			return (*this);
		}

		pointer operator->()
		{
			return p;
		}

		const_pointer operator->() const
		{
			return p;
		}

		reference operator[](int index)
		{
			return *(p + index);
		}

		const_reference operator[](int index) const
		{
			return *(p + index);
		}
		
		template < class Iterator >
			bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() == rhs.base(); }
		template < class Iterator >
			bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return !operator==(lhs, rhs); }
		template < class Iterator >
			bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return rhs.base() < lhs.base(); }
		template < class Iterator >
			bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return !operator<=(lhs, rhs); }
		template < class Iterator >
			bool operator<=  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return !operator>(rhs, lhs); }
		template < class Iterator >
			bool operator>=  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return !operator<(lhs, rhs); }
		
		template <class Iterator>
			reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return reverse_iterator<Iterator> (rev_it.base() + n);	}
		template <class Iterator>
			reverse_iterator<Iterator> operator- ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return reverse_iterator<Iterator> (rev_it.base() - n);	}

		template <class Iterator>
  			typename reverse_iterator<Iterator>::difference_type operator- ( const reverse_iterator<Iterator>& lhs,  const reverse_iterator<Iterator>& rhs){return reverse_iterator<Iterator> ( return (rhs.base() - lhs.base()); }
	};
}