/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:08:09 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/06 17:56:50 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "myRedBlackTree.cpp"
#include "pair.hpp"
#include "mapIterator.hpp"
#include "../vector/vector.hpp"

namespace ft  {
	
	 template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
			>
	class map
	{
		private:
			RedBlackTree<ft::pair< const Key, T>, Compare, Alloc> _rbt;
			Compare _cmp;
			Alloc _alloc;
			size_type _size;
		public:
			typedef Key			key_type;
			typedef T			mapped_type;
			typedef ft::pair<const key_type,mapped_type> value_type;
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

			template <class Key, class T, class Compare, class Alloc>
			class value_compare : public std::binary_function<value_type,value_type,bool>
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			}
		
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

			mapped_type& operator[] (const key_type& k) { return (*((this->insert(make_pair(k,mapped_type()))).first)).second; }
			
			// insert
			pair<iterator,bool> insert (const value_type& val)
			{
				RedBlackNode *tmp = this->_rbt.search(val);
				bool found = false;
				if (tmp == NULL)
				{
					found = true;
					this->_rbt.insert(val);
					tmp = this->_rbt.search(val);
					this->_size++;
				}
				return ft::make_pair(iterator(tmp, &this->_rbt), found);
			}
			
			iterator insert (iterator position, const value_type& val)
			{
				this->_size++;
				return (this->insert(val)).first;
			}
			template <class InputIterator>
  				void insert (InputIterator first, InputIterator last)
				{
					_size++;
					while (first != last)
					{
						this->insert(*first);
						++first;
					}
				}
				
			// erase
			void erase (iterator position) { this->_rbt.deleteByVal(position->first);}
			
			size_type erase (const key_type& k)
			{
				this->_size--;
				return this->_rbt.deleteByVal(k);
			}
			void erase (iterator first, iterator last)
			{
				ft::Vector<key_t> tmp;
				
				while (first != last)
				{
					tmp.push_back(first->first);
					++first;
				}
				for (size_type i = 0; i < tmp.size(); i++)
				{
					this->_rbt.deleteByVal(tmp[i]);
				}
			}
			
			void swap (map& x)
			{
				this->_rbt.swap(x._rbt);
				this->_rbt.swap(this->_size, x._size);
			}
			
			void clear() { this->_rbt.clear(); }


			key_compare key_comp() const
			{
				return this->_cmp;
			}
			value_compare value_comp() const
			{
				return value_compare(_cmp);
			}


			iterator find (const key_type& k)
			{
				return this->_rbt.find(k);
			}
			const_iterator find (const key_type& k) const
			{
				return this->_rbt.find(k);
			}

			size_type count (const key_type& k) const
			{
				return this->_rbt.count(k);
			}

			iterator lower_bound (const key_type& k)
			{
				return this->_rbt.lower_bound(k);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return this->_rbt.lower_bound(k);
			}

			iterator upper_bound (const key_type& k)
			{
				return this->_rbt.upper_bound(k);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return this->_rbt.upper_bound(k);
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