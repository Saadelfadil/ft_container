/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcadmin <mcadmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:43:04 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/09 02:12:22 by mcadmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include "../../Vector/iterator_traits.hpp"
#include "mapIterator.hpp"

namespace ft {
	
	template <class Iterator>
	class map_reverse_iterator {
		public:
			typedef Iterator iterator_type;
			typedef typename  Iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename  Iterator_traits<Iterator>::value_type value_type;
			typedef typename  Iterator_traits<Iterator>::difference_type difference_type;
			typedef typename  Iterator_traits<Iterator>::pointer pointer;
			typedef typename  Iterator_traits<Iterator>::pointer const *const_pointer;
			typedef typename  Iterator_traits<Iterator>::reference reference;
			typedef typename  Iterator_traits<Iterator>::reference const &const_reference;
			
		protected:
			iterator_type _iterator;
		public:
		
		map_reverse_iterator() : _iterator(iterator_type()) {};

		explicit map_reverse_iterator (iterator_type it) { this->_iterator = --it; };
		
		iterator_type base() const { return (this->_iterator + 1); }
	
		template <class Iter>
		map_reverse_iterator (const map_reverse_iterator<Iter>& rev_it)  {
			iterator_type it = rev_it.base();
			it = it - 1;
			_iterator = it;
		};

		virtual ~map_reverse_iterator(){};
		
		reference operator*() {return *this->_iterator;}
		
		const_pointer operator*() const  {return *this->_iterator;}

		map_reverse_iterator operator+(difference_type n) const {return(map_reverse_iterator(_iterator - n + 1));}

		map_reverse_iterator operator-(difference_type n) const {return(map_reverse_iterator(_iterator + n + 1));}
		
		map_reverse_iterator &operator++() {--_iterator; return *this;}

		map_reverse_iterator operator++(int) {map_reverse_iterator tmp = *this ; --_iterator; return tmp;}

		map_reverse_iterator &operator--() {++_iterator; return *this;}

		map_reverse_iterator operator--(int) {map_reverse_iterator tmp = *this ; ++_iterator; return tmp;}
		
		map_reverse_iterator &operator+=(difference_type  value) {_iterator -= value; return (*this);}
		
		map_reverse_iterator &operator-=(difference_type  value)	{ _iterator += value; return (*this);}

		pointer operator->() {return &*_iterator;}

		const_pointer operator->() const {return &*_iterator;}

		reference operator[](int index)	{return *(this->_iterator + index);}

		const_reference operator[](int index) const	{return *(this->_iterator + index);}

		operator map_reverse_iterator<const iterator_type>() const {
                return (map_reverse_iterator<const iterator_type>(_iterator));
            }
	};
	
	template < class T >
		bool operator== (const map_reverse_iterator<T>& lhs, const map_reverse_iterator<T>& rhs) { return lhs.base() == rhs.base(); }
	template < class T >
		bool operator!= (const map_reverse_iterator<T>& lhs, const map_reverse_iterator<T>& rhs) { return !operator==(lhs, rhs); }
	template < class T >
		bool operator<  (const map_reverse_iterator<T>& lhs, const map_reverse_iterator<T>& rhs) { return lhs.base() > rhs.base(); }
	template < class T >
		bool operator>  (const map_reverse_iterator<T>& lhs, const map_reverse_iterator<T>& rhs) { return lhs.base() < rhs.base(); }
	template < class T >
		bool operator<=  (const map_reverse_iterator<T>& lhs, const map_reverse_iterator<T>& rhs) { return lhs.base() >= rhs.base(); }
	template < class T >
		bool operator>=  (const map_reverse_iterator<T>& lhs, const map_reverse_iterator<T>& rhs) { return lhs.base() <= rhs.base(); }
	
	template <class Iterator>
		map_reverse_iterator<Iterator> operator+ ( typename map_reverse_iterator<Iterator>::difference_type n, const map_reverse_iterator<Iterator>& rev_it)
		{ return (rev_it + n);	}
		
	template <class Iterator>
		typename map_reverse_iterator<Iterator>::difference_type operator- ( const map_reverse_iterator<Iterator>& lhs,  const map_reverse_iterator<Iterator>& rhs)
		{return (rhs.base() - lhs.base()); }
}