/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myRedBlackTree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/13 15:53:54 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

struct RedBlack
{
	int data;
	RedBlack *parent;    
	RedBlack *right;    
	RedBlack *left;
	int color;    
};

	typedef RedBlack *RedBlackNode;
class RedBlackTree
{
	private:
  		RedBlackNode root;
  		RedBlackNode TNULL;
	public:
		void insertion(int key)
		{
			RedBlackNode myTree;
			RedBlackNode y;
			RedBlackNode x;

			myTree->parent = nullptr;
			myTree->data = key;
			myTree->right = TNULL;
			myTree->left = TNULL;
			myTree->color = 1;

			y = nullptr;
			x = this->root;
		}
};