/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myRedBlackTree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/20 13:01:01 by sel-fadi         ###   ########.fr       */
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
				RedBlack *tmp = node->parent;
				if (tmp)
					return (node == tmp->left);
				return false;
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
			RedBlack *sibling()
			{
				RedBlack *node;
				// sibling null if no parent
				if (node->parent == NULL)
					return NULL;
				if (isOnLeft(node))
					return node->parent->right;
				return node->parent->left;
			}
			// 6 - deletion
			void fixDoubleBlack(RedBlack *x)
			{
				if (x == root)
				// Reached root
					return;
			
				RedBlack *sibling;
				RedBlack *parent = x->parent;
				if (sibling == NULL)
				{
					// No sibiling, double black pushed up
					fixDoubleBlack(parent);
				}
				else
				{
					if (sibling->color == RED)
					{
						// Sibling red
						parent->color = RED;
						sibling->color = BLACK;
						if (isOnLeft(sibling))
						{
							// left case
							rotateRight(root, parent);
						}
						else
						{
							// right case
							rotateLeft(root, parent);
						}
						fixDoubleBlack(x);
					}
					else
					{
						// Sibling black
						if (hasRedChild(sibling))
						{
							// at least 1 red children
							if (sibling->left != NULL and sibling->left->color == RED)
							{
								if (isOnLeft(sibling))
								{
									// left left
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									rotateRight(root, parent);
								}
								else
								{
									// right left
									sibling->left->color = parent->color;
									rotateRight(root, sibling);
									rotateLeft(root, parent);
								}
							}
							else
							{
								if (isOnLeft(sibling))
								{
									// left right
									sibling->right->color = parent->color;
									rotateLeft(root, sibling);
									rotateRight(root, parent);
								}
								else
								{
									// right right
									sibling->right->color = sibling->color;
									sibling->color = parent->color;
									rotateLeft(root, parent);
								}
							}
							parent->color = BLACK;
						}
						else
						{
							// 2 black children
							sibling->color = RED;
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
			RedBlack *BSTreplace(RedBlack *x)
			{
				// when node have 2 children
				if (x->left != NULL && x->right != NULL)
					return successor(x->right);
			
				// when leaf
				if (x->left == NULL && x->right == NULL)
					return NULL;
			
				// when single child
				if (x->left != NULL)
					return x->left;
				else
					return x->right;
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
			void deleteNode(RedBlack *v)
			{
				RedBlack *u = BSTreplace(v);
			
				// True when u and v are both black
				bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
				RedBlack *parent = v->parent;
			
				if (u == NULL) 
				{
					// u is NULL therefore v is leaf
					if (v == root)
					{
						// v is root, making root null
						root = NULL;
					}
					else
					{
						if (uvBlack)
						{
							// u and v both black
							// v is leaf, fix double black at v
							fixDoubleBlack(v);
						}
						else
						{
							// u or v is red
							if (sibling() != NULL)
								// sibling is not null, make it red"
								sibling()->color = RED;
						}
						// delete v from the tree
						if (isOnLeft(u))
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					delete v;
					return;
				}
			
				if (v->left == NULL or v->right == NULL)
				{
					// v has 1 child
					if (v == root)
					{
						// v is root, assign the value of u to v, and delete u
						v->data->first = u->data->first;
						v->left = v->right = NULL;
						delete u;
					}
					else
					{
						// Detach v from tree and move u up
						if (isOnLeft(u))
							parent->left = u;
						else
							parent->right = u;
						delete v;
						u->parent = parent;
						if (uvBlack)
							// u and v both black, fix double black at u
							fixDoubleBlack(u);
						else
							// u or v red, color u black
							u->color = BLACK;
					}
					return;
				}
				// v has 2 children, swap values with successor and recurse
				swapValues(u, v);
				deleteNode(u);
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
			
				RedBlack *v = search(val);
				if (v == NULL)
				{
					std::cout << "not found\n";
					return ;
				}
				deleteNode(v);
			}
			

			/* --------- another deletion test ----------- */

			// void rotateLeft(RedBlack *&x) {
			// 	RedBlack *y = x->right;
			// 	x->right = y->left;
			// 	if (y->left != NULL) {
			// 	y->left->parent = x;
			// 	}
			// 	y->parent = x->parent;
			// 	if (x->parent == nullptr) {
			// 	this->root = y;
			// 	} else if (x == x->parent->left) {
			// 	x->parent->left = y;
			// 	} else {
			// 	x->parent->right = y;
			// 	}
			// 	y->left = x;
			// 	x->parent = y;
			// }

			// void rotateRight(RedBlack *&x) {
			// 	RedBlack *y = x->left;
			// 	x->left = y->right;
			// 	if (y->right != NULL) {
			// 	y->right->parent = x;
			// 	}
			// 	y->parent = x->parent;
			// 	if (x->parent == nullptr) {
			// 	this->root = y;
			// 	} else if (x == x->parent->right) {
			// 	x->parent->right = y;
			// 	} else {
			// 	x->parent->left = y;
			// 	}
			// 	y->right = x;
			// 	x->parent = y;
			// }
			// // For balancing the tree after deletion
			// void deleteFix(RedBlack *&x)
			// {
			// 	RedBlack *s;
			// 	while (x != root && x->color == 0)
			// 	{
			// 		if (x == x->parent->left)
			// 		{
			// 			s = x->parent->right;
			// 			if (s->color == 1)
			// 			{
			// 				s->color = 0;
			// 				x->parent->color = 1;
			// 				rotateLeft(x->parent);
			// 				s = x->parent->right;
			// 			}

			// 			if (s->left->color == 0 && s->right->color == 0)
			// 			{
			// 				s->color = 1;
			// 				x = x->parent;
			// 			}
			// 			else
			// 			{
			// 				if (s->right->color == 0)
			// 				{
			// 					s->left->color = 0;
			// 					s->color = 1;
			// 					rotateRight(s);
			// 					s = x->parent->right;
			// 				}

			// 				s->color = x->parent->color;
			// 				x->parent->color = 0;
			// 				s->right->color = 0;
			// 				rotateLeft(x->parent);
			// 				x = root;
			// 			}
			// 		}
			// 		else
			// 		{
			// 			s = x->parent->left;
			// 			if (s->color == 1)
			// 			{
			// 				s->color = 0;
			// 				x->parent->color = 1;
			// 				rotateRight(x->parent);
			// 				s = x->parent->left;
			// 			}

			// 			if (s->right->color == 0 && s->right->color == 0)
			// 			{
			// 			s->color = 1;
			// 			x = x->parent;
			// 			}
			// 			else
			// 			{
			// 				if (s->left->color == 0)
			// 				{
			// 					s->right->color = 0;
			// 					s->color = 1;
			// 					rotateLeft(s);
			// 					s = x->parent->left;
			// 				}

			// 				s->color = x->parent->color;
			// 				x->parent->color = 0;
			// 				s->left->color = 0;
			// 				rightRotate(x->parent);
			// 				x = root;
			// 			}
			// 		}
			// 	}
			// 	x->color = 0;
			// }
  
			// RedBlack *minimum(RedBlack *node)
			// {
			// 	while (node->left != NULL)
			// 		node = node->left;
			// 	return node;
			// }

			// RedBlack *maximum(RedBlack *node)
			// {
			// 	while (node->right != NULL)
			// 		node = node->right;
			// 	return node;
			// }

			// RedBlack successor(RedBlack *x)
			// {
			// 	if (x->right != NULL)
			// 		return minimum(x->right);

			// 	RedBlack y = x->parent;
			// 	while (y != NULL && x == y->right)
			// 	{
			// 		x = y;
			// 		y = y->parent;
			// 	}
			// 	return y;
			// }

			// RedBlack predecessor(RedBlack *x)
			// {
			// 	if (x->left != NULL)
			// 		return maximum(x->left);

			// 	RedBlack *y = x->parent;
			// 	while (y != NULL && x == y->left)
			// 	{
			// 		x = y;
			// 		y = y->parent;
			// 	}
			// 	return y;
			// }
			
			// void rbTransplant(RedBlack *u, RedBlack *v)
			// {
			// 	if (u->parent == NULL)
			// 		root = v;
			// 	else if (u == u->parent->left)
			// 		u->parent->left = v;
			// 	else
			// 		u->parent->right = v;
			// 	v->parent = u->parent;
			// }
			
			// void deleteNodeHelper(RedBlack *&node, value_type *key)
			// {
			// 	RedBlack *z = NULL;
			// 	RedBlack *x, *y;
			// 	while (node != NULL)
			// 	{
			// 		if (node->data->first == key->first)
			// 			z = node;
			// 		if (node->data->first <= key->first)
			// 			node = node->right;
			// 		else
			// 			node = node->left;
			// 	}
			// 	if (z == NULL)
			// 	{
			// 		std::cout << "Key not found in the tree" << std::endl;
			// 		return;
			// 	}
			// 	y = z;
			// 	int y_original_color = y->color;
			// 	if (z->left == NULL)
			// 	{
			// 		x = z->right;
			// 		rbTransplant(z, z->right);
			// 	}
			// 	else if (z->right == NULL)
			// 	{
			// 		x = z->left;
			// 		rbTransplant(z, z->left);
			// 	}
			// 	else
			// 	{
			// 		y = minimum(z->right);
			// 		y_original_color = y->color;
			// 		x = y->right;
			// 		if (y->parent == z)
			// 			x->parent = y;
			// 		else
			// 		{
			// 			rbTransplant(y, y->right);
			// 			y->right = z->right;
			// 			y->right->parent = y;
			// 		}

			// 		rbTransplant(z, y);
			// 		y->left = z->left;
			// 		y->left->parent = y;
			// 		y->color = z->color;
			// 	}
			// 	delete z;
			// 	if (y_original_color == 0)
			// 		deleteFix(x);
			// }
			
			// void deleteNode(value_type *data)
			// {
			// 	deleteNodeHelper(this->root, data);
			// }

			
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
		std::pair<int, int> f9 = std::make_pair(37, 10);
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
		redblack.deleteByVal(&f8);

		redblack.print();

		// bst.printTree();
		}

