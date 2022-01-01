/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcadmin <mcadmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:29:15 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/01 18:34:16 by mcadmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Vector/iterator_traits.hpp"

namespace ft
{
    template < class T, class Node, class Tree >
    class MapIterator {
        protected:
            Node *_node;
            Tree *_rbt;
        public:
			typedef Iterator_traits< iterator<std::bidirectional_iterator_tag, T> > iterator_traits;
			typedef typename iterator_traits::value_type value_type;
			typedef typename iterator_traits::pointer pointer;
			typedef typename iterator_traits::reference reference;
			typedef typename iterator_traits::difference_type difference_type;
			typedef typename iterator_traits::iterator_category iterator_category;
            typedef MapIterator<const T, const Node, Tree> const_iterator;
        
            MapIterator() : _node(), _rbt() {};
            MapIterator( Node *node, const Tree *rbt ) : _node(node), _rbt(rbt) {};
            MapIterator( const MapIterator& rhs ) { *this = rhs; }
            MapIterator& operator= ( const MapIterator& rhs ) { this->_node = rhs._node; this->_rbt = rhs._rbt; return *this; }
            virtual ~MapIterator() {};

            reference operator*() const { return *this->_node->data; }
            pointer   operator->() const { return this->_node->data; }

            MapIterator operator++ ()
            {
                Node *p;
                if (_node == NULL)
                {
                    // ++ from end(). get the root of the _rbt
                    _node = _rbt->root;
                    
                    // error! ++ requested for an empty _rbt
                    if (_node == NULL)
                        throw "mmmmkkk";
                    
                    // move to the smallest value in the _rbt,
                    // which is the first node inorder
                    while (_node->left != NULL) {
                        _node = _node->left;
                    }
                }
                else
                    if (_node->right != NULL)
                    {
                        _node = _node->right;
                        while (_node->left != NULL) {
                            _node = _node->left;
                        }
                    }
                    else
                    {
                        p = _node->parent;
                        while (p != NULL && _node == p->right) {
                            _node = p;
                            p = p->parent;
                        }
                        _node = p;
                    }
                return *this;
            }
            MapIterator operator-- ()
            {
                Node *p;
                if (_node == NULL)
                {
                    // ++ from end(). get the root of the _rbt
                    _node = _rbt->root;
                    
                    // error! ++ requested for an empty _rbt
                    if (_node == NULL)
                        throw "mmmmkkk";
                    
                    // move to the smallest value in the _rbt,
                    // which is the first node inorder
                    while (_node->right != NULL) {
                        _node = _node->right;
                    }
                }
                else
                    if (_node->left != NULL)
                    {
                        _node = _node->left;
                        while (_node->right != NULL) {
                            _node = _node->right;
                        }
                    }
                    else
                    {
                        p = _node->parent;
                        while (p != NULL && _node == p->left) {
                            _node = p;
                            p = p->parent;
                        }
                        _node = p;
                    }
                return *this;
            }

            Node *base() const { return this->_node;}

            operator const_iterator() const { return const_iterator(_node, _rbt);}
    };
    
    template < class T, class Node, class Tree>
        bool operator== (const MapIterator<T, Node, Tree>& lhs, const MapIterator<T, Node, Tree>& rhs) { return lhs.base() == rhs.base(); }
    template < class T, class Node, class Tree>
        bool operator!= (const MapIterator<T, Node, Tree>& lhs, const MapIterator<T, Node, Tree>& rhs) { return !operator==(lhs, rhs); }
}