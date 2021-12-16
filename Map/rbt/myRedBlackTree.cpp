/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myRedBlackTree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/16 19:33:12 by sel-fadi         ###   ########.fr       */
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

	class RedBlackTree
	{
		private:
			RedBlack *root;
		public:
			RedBlackTree()
			{
				this->root = nullptr;
			}
			
			void rotateLeft(RedBlack *&root, RedBlack *&node)
			{
				RedBlack *node_right = node->right;
			
				node->right = node_right->left;
			
				if (node->right != NULL)
					node->right->parent = node;
			
				node_right->parent = node->parent;
			
				if (node->parent == NULL)
					root = node_right;
				else if (node == node->parent->left)
					node->parent->left = node_right;
				else
					node->parent->right = node_right;
			
				node_right->left = node;
				node->parent = node_right;
			}
			
			void rotateRight(RedBlack *&root, RedBlack *&node)
			{
				RedBlack *node_left = node->left;
			
				node->left = node_left->right;
			
				if (node->left != NULL)
					node->left->parent = node;
			
				node_left->parent = node->parent;
			
				if (node->parent == NULL)
					root = node_left;
				else if (node == node->parent->left)
					node->parent->left = node_left;
				else
					node->parent->right = node_left;
			
				node_left->right = node;
				node->parent = node_left;
			}

			void fixViolation(RedBlack *root, RedBlack *newNode)
			{
				RedBlack *parent_newNode = NULL;
				RedBlack *grand_parent_newNode = NULL;

				while ((newNode != root) && (newNode->color != BLACK) && (newNode->parent->color == RED))
				{
					parent_newNode = newNode->parent;
					grand_parent_newNode = newNode->parent->parent;

					/*  Case : A ---> Parent of newNode is left child of Grand-parent of newNode */
					if (parent_newNode == grand_parent_newNode->left)
					{
						RedBlack *uncle_newNode = grand_parent_newNode->right;
						/* Case : 1  The uncle of newNode is also red Only Recoloring required */
						if (uncle_newNode != NULL && uncle_newNode->color == RED)
						{
							grand_parent_newNode->color = RED;
							parent_newNode->color = BLACK;
							uncle_newNode->color = BLACK;
							newNode = grand_parent_newNode;
						}
						else
						{
							/* Case : 2  newNode is right child of its parent  Left-rotation required */
							if (newNode == parent_newNode->right)
							{
								rotateLeft(root, parent_newNode);
								newNode = parent_newNode;
								parent_newNode = newNode->parent;
							}
							/* Case : 3  newNode is left child of its parent Right-rotation required */
							rotateRight(root, grand_parent_newNode);
							std::swap(parent_newNode->color, grand_parent_newNode->color);
							newNode = parent_newNode;
						}
					}

					/* Case : B  Parent of newNode is right child of Grand-parent of newNode */
					else
					{
						 RedBlack *uncle_newNode = grand_parent_newNode->left;
 
						/*  Case : 1 The uncle of newNode is also red Only Recoloring required */
						if ((uncle_newNode != NULL) && (uncle_newNode->color == RED))
						{
							grand_parent_newNode->color = RED;
							parent_newNode->color = BLACK;
							uncle_newNode->color = BLACK;
							newNode = grand_parent_newNode;
						}
						else
						{
							/* Case : 2 newNode is left child of its parent Right-rotation required */
							if (newNode == parent_newNode->left)
							{
								rotateRight(root, parent_newNode);
								newNode = parent_newNode;
								parent_newNode = newNode->parent;
							}
			
							/* Case : 3 newNode is right child of its parent Left-rotation required */
							rotateLeft(root, grand_parent_newNode);
							std::swap(parent_newNode->color, grand_parent_newNode->color);
							newNode = parent_newNode;
						}
					}
				}
				root->color = BLACK;
			}
			
			void insertion(value_type *val)
			{
				RedBlack *newNode = new RedBlack(val);

				// Do a normal BST insert
				root = insertionBST(root, newNode);
				
				// fix Red Black Tree violations
				fixViolation(root, newNode);
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

// 	int main() {
// 		std::pair<int, int> value_type;

// 		ft::RedBlack RedBlack(std::pair<int, int> value_type);
// 		RedBlackTree redblack;
// 		redblack.insertion(55);
// 		redblack.insertion(40);
// 		redblack.insertion(65);
// 		redblack.insertion(60);
// 		redblack.insertion(75);
// 		redblack.insertion(57);
// 		redblack.insertion(56);
// 		redblack.insertion(64);

// 		redblack.printTree();
// 		// cout << endl
// 		//    << "After deleting" << endl;
// 		// bst.deleteNode(40);
// 		// bst.printTree();
// 		}
// }

