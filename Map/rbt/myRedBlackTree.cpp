/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myRedBlackTree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/14 20:22:28 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

enum Color {RED, BLACK};

struct RedBlack
{
	int data;
	RedBlack *parent;    
	RedBlack *right;    
	RedBlack *left;
	bool color;
};
typedef RedBlack *RedBlackNode;


class RedBlackTree
{
	private:
  		RedBlackNode root;
	public:
		RedBlackTree()
		{
			this->root = nullptr;
		}
		void insertion(RedBlack key)
		{
			RedBlackNode myTree;
			RedBlackNode y;
			RedBlackNode x;

			myTree->parent = nullptr;
			myTree->data = key;
			myTree->right = nullptr;
			myTree->left = nullptr;
			myTree->color = 1;

			y = nullptr;
			x = this->root;
		}
};