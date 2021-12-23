/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myRedBlackTree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/23 11:52:52 by sel-fadi         ###   ########.fr       */
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
			
			RedBlack *insertionBST(RedBlack *src , RedBlack *newNode)
			{
				/* If the tree is empty, return a new node */
				if (src == NULL)
					return newNode;
				/* Otherwise, recur down the tree */
				if (newNode->data->first < src->data->first)
				{
					src->left  = insertionBST(src->left, newNode);
					src->left->parent = src;
				}
				else if (newNode->data->first > src->data->first)
				{
					src->right = insertionBST(src->right, newNode);
					src->right->parent = src;
				}
			
				/* return the (unchanged) node pointer */
				return src;
			}
			
			void insertion(value_type *val)
			{
				RedBlack *newNode = new RedBlack(val);

				// Do a normal BST insert
				root = insertionBST(root, newNode);
				
				// fix Red Black Tree violations
				fixViolation(root, newNode);
			}

			// 9 - deletion
			// find node that do not have a left child
			// in the subtree of the given node
			RedBlack *successor(RedBlack *x)
			{
				RedBlack *temp = x;
			
				while (temp->left != NULL)
					temp = temp->left;
			
				return temp;
			}
			// 8 - deletion
			// check if node is left child of parent
 			bool isOnLeft(RedBlack *node)
			{
				if (node == NULL)
					return false;
				return (node == node->parent->left);
			}
			 // moves node down and moves given node in its place
			// void moveDown(RedBlack *nParent) {
			// 	if (parent != NULL) {
			// 	if (isOnLeft()) {
			// 		parent->left = nParent;
			// 	} else {
			// 		parent->right = nParent;
			// 	}
			// 	}
			// 	nParent->parent = parent;
			// 	parent = nParent;
			// }
			
			bool hasRedChild(RedBlack *node)
			{
				return (node->left != NULL && node->left->color == RED) ||
					(node->right != NULL && node->right->color == RED);
			}
			
			// 7 - deletion
			// returns pointer to sibling
			RedBlack *sibling(RedBlack *nodeTarget)
			{
				RedBlack *node = nodeTarget;
				// sibling null if no parent
				if (node->parent == NULL)
					return NULL;
				if (isOnLeft(node))
					return node->parent->right;
				return node->parent->left;
			}
			// 6 - deletion -----------------------------------------------
			void fixDoubleBlack(RedBlack *targetNode)
			{
				if (targetNode == root)
				// Reached root
					return;
			
				RedBlack *sib = sibling(targetNode);
				RedBlack *parent = targetNode->parent;
				if (sib == NULL)
				{
					// No sibiling, double black pushed up
					fixDoubleBlack(parent);
				}
				else
				{
					if (sib->color == RED)
					{
						// sib red
						parent->color = RED;
						sib->color = BLACK;
						if (isOnLeft(sib))
						{
							// left case
							rotateRight(root, parent);
						}
						else
						{
							// right case
							rotateLeft(root, parent);
						}
						fixDoubleBlack(targetNode);
					}
					else
					{
						// Sibling black
						if (hasRedChild(sib))
						{
							// at least 1 red children
							if (sib->left != NULL && sib->left->color == RED)
							{
								if (isOnLeft(sib))
								{
									// left left
									sib->left->color = sib->color;
									sib->color = parent->color;
									rotateRight(root, parent);
								}
								else
								{
									// right left
									sib->left->color = parent->color;
									rotateRight(root, sib);
									rotateLeft(root, parent);
								}
							}
							else
							{
								if (isOnLeft(sib))
								{
									// left right
									sib->right->color = parent->color;
									rotateLeft(root, sib);
									rotateRight(root, parent);
								}
								else
								{
									// right right
									sib->right->color = sib->color;
									sib->color = parent->color;
									rotateLeft(root, parent);
								}
							}
							parent->color = BLACK;
						}
						else
						{
							// 2 black children
							sib->color = RED;
							if (parent->color == BLACK)
								fixDoubleBlack(parent);
							else
								parent->color = BLACK;
						}
					}
				}
			}
			// 5 - deletion
			// find node that replaces a deleted node in BST
			RedBlack *BSTreplace(RedBlack *&targetNode)
			{
				// when node have 2 children
				if (targetNode->left != NULL && targetNode->right != NULL)
					return successor(targetNode->right);
			
				// when leaf
				if (targetNode->left == NULL && targetNode->right == NULL)
					return NULL;
			
				// when single child
				if (targetNode->left != NULL)
					return targetNode->left;
				else
					return targetNode->right;
			}
			// 4 - deletion
			void swapValues(RedBlack *u, RedBlack *v)
			{
				int tmp;
				tmp = u->data->first;
				u->data->first = v->data->first;
				v->data->first = tmp;
			}
			// 3 - deletion
			// deletes the given node
			void deleteNode(RedBlack *&targetNode)
			{
				RedBlack *nodeReplaceTarget = BSTreplace(targetNode);
			
				// True when u and v are both black
				bool rtBlack = ((nodeReplaceTarget == NULL || nodeReplaceTarget->color == BLACK) && (targetNode->color == BLACK));
				RedBlack *parentTarget = targetNode->parent;
			
				if (nodeReplaceTarget == NULL) 
				{
					// nodeReplaceTarget is NULL therefore targetNode is leaf
					if (targetNode == root)
					{
						// targetNode is root, making root null
						root = NULL;
					}
					else
					{
						if (rtBlack)
						{
							// u and targetNode both black
							// targetNode is leaf, fix double black at targetNode
							fixDoubleBlack(targetNode);
						}
						else
						{
							RedBlack *tmp = sibling(targetNode);
							// u or targetNode is red
							if (tmp != NULL)
								// sibling is not null, make it red"
								tmp->color = RED;
						}
						// delete targetNode from the tree
						if (isOnLeft(targetNode))
							parentTarget->left = NULL;
						else
							parentTarget->right = NULL;
					}
					delete targetNode;
					return;
				}
			
				if (targetNode->left == NULL || targetNode->right == NULL)
				{
					// targetNode has 1 child
					if (targetNode == root)
					{
						// targetNode is root, assign the value of u to targetNode, and delete u
						targetNode->data->first = nodeReplaceTarget->data->first;
						targetNode->left = targetNode->right = NULL;
						delete nodeReplaceTarget;
					}
					else
					{
						// Detach targetNode from tree and motargetNodee u up
						if (isOnLeft(targetNode))
							parentTarget->left = nodeReplaceTarget;
						else
							parentTarget->right = nodeReplaceTarget;
						delete targetNode;
						nodeReplaceTarget->parent = parentTarget;
						if (rtBlack)
							// u and v both black, fix double black at u
							fixDoubleBlack(nodeReplaceTarget);
						else
							// u or v red, color u black
							nodeReplaceTarget->color = BLACK;
					}
					return;
				}
				// v has 2 children, swap values with successor and recurse
				swapValues(nodeReplaceTarget, targetNode);
				deleteNode(nodeReplaceTarget);
			}

			
			// 2 - deletion
			// searches for given value
			// if found returns the node (used for delete)
			// else returns the last node while traversing (used in insert)
			RedBlack *search(value_type *val)
			{
				RedBlack *tmp = root;
				while (1)
				{
					if (tmp == NULL)
						return NULL;
					if (val->first == tmp->data->first)
						return tmp;
					if (val->first < tmp->data->first)
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return tmp;
			}
			
			// 1 - deletion
			void deleteByVal(value_type *val)
			{
				// Tree is empty
				if (root == NULL)
					return;
			
				RedBlack *targetNode = search(val);
				if (targetNode == NULL)
				{
					std::cout << "not found\n";
					return ;
				}
				deleteNode(targetNode);
			}
			
		public:
			void    print() { if (this->root) this->printHelper(this->root, nullptr, false); std::cout << std::endl;}

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

	int main()
	 {
		ft::RedBlackTree<std::pair<int, int> > redblack;
		std::pair<int, int> f  = std::make_pair(55, 1);
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
		
		std::cout << std::endl
		   << "After Insertion" << std::endl;
		redblack.print();
		
		std::cout << std::endl
		   << "After deleting" << std::endl;
		
		redblack.deleteByVal(&f8);
		redblack.deleteByVal(&f6);
		redblack.deleteByVal(&f7);
		redblack.deleteByVal(&f4);
		redblack.deleteByVal(&f);
		redblack.deleteByVal(&f2);
		redblack.deleteByVal(&f5);
		redblack.print();
		}

