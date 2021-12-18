/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myRedBlackTree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/18 16:39:26 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <utility>
#include "pair.hpp"

namespace ft {

	enum Color {BLACK, RED};

	template < class value_pair,                                     // map::key_type
           class Compare = std::less<typename value_pair::first_type>,                     // map::key_compare
           class Alloc = std::allocator<value_pair >    // map::allocator_type
           >
	class RedBlackTree
	{
		public:
		typedef typename value_pair::first_type key;
		typedef typename value_pair::second_type value;

		typedef std::pair<key, value> value_type;

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
			
				if (node->left != NULL)
					node->left->parent = node;
			
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
			
				if (node->right != NULL)
					node->right->parent = node;
			
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

			void fixViolation(RedBlack *&root, RedBlack *&newNode)
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
				if (root == NULL)
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

		public:
			void    print() { if (this->root) this->printHelper(this->root, nullptr, false); }

		private:
                    /* ---------- | Recursive print of a "RBT" | ---------- */
            struct Trunk {
                Trunk *prev;
                std::string str;
                Trunk( Trunk *prev, std::string str ) { this->prev = prev; this->str = str; }
            };
            void showTrunks(Trunk *p) {
                if (p == nullptr) { return ; }
                showTrunks(p->prev);
                std::cout << p->str;
            }
            void printHelper( RedBlack* root, Trunk *prev, bool isLeft ) {
                if (root == nullptr) { return; }
                std::string prev_str = "    ";
                Trunk *trunk = new Trunk(prev, prev_str);
                printHelper(root->right, trunk, true);
                if (!prev) { trunk->str = "——— "; }
                else if (isLeft) { trunk->str = " .——— "; prev_str = "   |"; }
                else { trunk->str = " `——— "; prev->str = prev_str; }
                showTrunks(trunk);
                std::string sColor = root->color ? "R" : "B";
                std::cout << root->data->first << "(" << sColor <<  ")" << std::endl;
                if (prev) { prev->str = prev_str; }
                trunk->str = "   |";
                printHelper(root->left, trunk, false);
            }
	};
}

	int main() {
		ft::RedBlackTree<std::pair<int, int> > redblack;
		std::pair<int, int> f = std::make_pair(55, 1);
		std::pair<int, int> f1 = std::make_pair(40, 2);
		std::pair<int, int> f2 = std::make_pair(65, 3);
		std::pair<int, int> f3 = std::make_pair(60, 4);
		std::pair<int, int> f4 = std::make_pair(75, 5);
		std::pair<int, int> f5 = std::make_pair(57, 6);
		std::pair<int, int> f6 = std::make_pair(56, 7);
		std::pair<int, int> f7 = std::make_pair(64, 8);
		std::pair<int, int> f8 = std::make_pair(12, 9);
		redblack.insertion(&f);
		redblack.insertion(&f1);
		redblack.insertion(&f2);
		redblack.insertion(&f3);
		redblack.insertion(&f4);
		redblack.insertion(&f5);
		redblack.insertion(&f6);
		redblack.insertion(&f7);
		redblack.insertion(&f8);
		
		redblack.print();
		// cout << endl
		//    << "After deleting" << endl;
		// bst.deleteNode(40);
		// bst.printTree();
		}

