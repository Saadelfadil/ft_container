/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:08:09 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/03 12:39:35 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "myRedBlackTree.cpp"
#include "pair.hpp"
#include "mapIterator.hpp"

namespace ft  {
	
	 template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
			>
	class map
	{
		private:
			RedBlackTree<std::pair< const Key, T>, Compare, Alloc> _rbt;
			Compare _cmp;
			Alloc _alloc;
		public:
			typedef Key			key_type;
			typedef T			mapped_type;
			typedef std::pair<const key_type,mapped_type> value_type;
			typedef Compare		key_compare;
			typedef Alloc		allocator_type;
			typedef typename    allocator_type::reference           reference;
			typedef typename    allocator_type::const_reference     const_reference;
			typedef typename    allocator_type::pointer             pointer;
			typedef typename    allocator_type::const_pointer       const_pointer;
			typedef typename	RedBlackTree<value_type,key_compare,allocator_type>::iterator iterator;
			typedef typename	RedBlackTree<value_type,key_compare,allocator_type>::const_iterator const_iterator;
			typedef typename	RedBlackTree<value_type,key_compare,allocator_type>::reverse_iterator reverse_iterator;
			typedef typename	RedBlackTree<value_type,key_compare,allocator_type>::const_reverse_iterator const_reverse_iterator;
			typedef	ptrdiff_t	difference_type;
			typedef	size_t		size_type;
		
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rbt(), _cmp(comp), _alloc(alloc) {}
            
            template <class InputIterator>
				map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rbt(first, last), _cmp(comp), _alloc(alloc) {}
            
            map (const map& x); { *this = x; }
			
			~map();
			
			map& operator= (const map& x); { this->_rbt = x._rbt; return *this; }

			
			iterator begin() { return this->_rbt.begin(); }
            const_iterator begin() const { return this->_rbt.begin(); }
            iterator end() { return this->_rbt.end(); }
            const_iterator end() const { return this->_rbt.end(); }
            reverse_iterator rbegin() { return this->_rbt.rbegin(); }
            const_reverse_iterator rbegin() const { return this->_rbt.rbegin(); }
            reverse_iterator rend() { return this->_rbt.rend(); }
            const_reverse_iterator rend() const { return this->_rbt.rend(); }

			bool empty() const { return this->_rbt.empty(); }
            size_type size() const { return this->_rbt.size(); }
            size_type max_size() const { return this->_rbt.max_size(); }

			mapped_type& operator[] (const key_type& k);
			
			// insert
			pair<iterator,bool> insert (const value_type& val)
			{
				return this->_rbt.insert(val);
			}
			iterator insert (iterator position, const value_type& val)
			{
				return this->_rbt.insert(position, val);
			}
			template <class InputIterator>
  				void insert (InputIterator first, InputIterator last) { return this->_rbt.insert(first, last); }
				
			// erase
			void erase (iterator position) { this->_rbt.erase(position);}
			
			size_type erase (const key_type& k)
			{
				return thiss->_rbt.erase(k);
			}
			void erase (iterator first, iterator last)
			{
				
			}
			
			void swap (map& x)
			{
				this->_rbt.swap(x._rbt);
			}
			
			void clear() { this->_rbt.clear(); }


			key_compare key_comp() const
			{
				
			}
			value_compare value_comp() const
			{
				
			}


			iterator find (const key_type& k)
			{
				
			}
			const_iterator find (const key_type& k) const
			{
				
			}

			size_type count (const key_type& k) const
			{
				
			}

			terator lower_bound (const key_type& k)
			{
				
			}
			const_iterator lower_bound (const key_type& k) const
			{
				
			}

			iterator upper_bound (const key_type& k)
			{
				
			}
			const_iterator upper_bound (const key_type& k) const
			{
				
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				
			}
			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				
			}


			allocator_type get_allocator() const
			{
				
			}
	};
}