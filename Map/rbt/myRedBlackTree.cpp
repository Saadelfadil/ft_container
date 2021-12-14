/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myRedBlackTree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/14 23:27:47 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <utility>
#include "pair.hpp"

namespace ft {

	enum Color {RED, BLACK};
	typedef std::pair<class key, class value> value_type;

	typedef struct RedBlack
	{
		value_type *data;
		RedBlack *parent;    
		RedBlack *right;    
		RedBlack *left;
		bool color;

		RedBlack(value_type *data)
		{
			this->data = data;
			left = right = parent = NULL;
			this->color = RED;
		}
		
	}		RedBlack;
	// typedef RedBlack *RedBlackNode;

	class RedBlackTree
	{
		private:
			RedBlack *root;
		public:
			RedBlackTree()
			{
				this->root = nullptr;
			}
			void insertion(value_type *val)
			{
				RedBlack *newNode = new RedBlack(val);

				root = insertionBST(root, newNode);
				// newNode->parent = nullptr;
				// newNode->data = val->first;
				// newNode->right = nullptr;
				// newNode->left = nullptr;
				// newNode->color = RED;
			}

			RedBlack *insertionBST(RedBlack *root , RedBlack *newNode)
			{
				/* If the tree is empty, return a new node */
				if (root == nullptr)
					return newNode;
				/* Otherwise, recur down the tree */
				if (newNode->data->first < root->data->first)
				{
					root->left  = insertionBST(root->left, newNode);
					root->left->parent = root;
				}
				else if (newNode->data->first > root->data->first)
				{
					root->right = insertionBST(root->right, newNode);
					root->right->parent = root;
				}
			
				/* return the (unchanged) node pointer */
				return root;
			}
	};


}