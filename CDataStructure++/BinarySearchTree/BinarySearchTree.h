#pragma once

#include <iostream>
#include "BinarySearchTreeNode.h"

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
		:
		root(nullptr),
		depth(0)
	{
	}

	//BinaryTree(BinaryTreeNode<T>* root)
	//	:
	//	root(root),
	//	depth(1)
	//{	
	//}

	BinarySearchTree(const T& data)
		:
		root(new BinarySearchTreeNode<T>(data)),
		depth(1)
	{
	}

	~BinarySearchTree()
	{
		cleanUpTree(root);
		depth = -1;
	}

	void cleanUpTree(BinarySearchTreeNode<T>* currNode)
	{
		// Post-order traversal to delete and free up memory taken by each node.
		// First the left three and right tree are visited and deleted first and then the current node is deleted so 
		// that everything descendent node is deleted first before deleting the current node to not lose reference
		// and cause memory leaks.
		if (currNode != nullptr)
		{
			if (currNode->hasLeft())
			{
				cleanUpTree(currNode->getLeft());
			}

			if (currNode->hasRight())
			{
				cleanUpTree(currNode->getRight());
			}

			delete currNode;
		}
	}

	// from https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
	void printTree(const std::string& prefix, BinarySearchTreeNode<T>* node, bool isLeft)
	{
		if (node != nullptr)
		{
			std::cout << prefix;

			std::cout << (isLeft ? "|-- " : "\\-- ");

			// print the value of the node
			std::cout << "(" << node->getData() << ")" << std::endl;

			// enter the next tree level - left and right branch
			printTree(prefix + (isLeft ? "|   " : "    "), node->getLeft(), true);
			printTree(prefix + (isLeft ? "|   " : "    "), node->getRight(), false);
		}
	}

	void printTree(BinarySearchTreeNode<T>* node = nullptr)
	{
		std::cout << "Printing the BST\n";
		std::cout << "|-- = left node (value < parent value)\n";
		std::cout << "\\-- = right/root node (value > parent value)\n\n";
		if (node == nullptr)
		{
			printTree("", root, false);
		}
		else
		{
			printTree("", node, false);
		}
	}

	void removeNode(const T& data, BinarySearchTreeNode<T>* parentNode, BinarySearchTreeNode<T>* currNode)
	{
		if (currNode != nullptr)
		{
			if (parentNode != nullptr)
			{
				
			}
			else
			{
				// TODO: root needs to be removed, find successor node and make the new root
				// If no right and then left node is present, make the right node the root
				// because there is no node that is smaller than the direct right node
			}
		}
	}

	void removeNode(const T& data)
	{
		return removeNode(data, nullptr, root);
	}

	void insertNode(const T& data)
	{
		const auto toAddNode = new BinarySearchTreeNode<T>(data);

		// if root is not pointing to a node yet, then just add the toAddNode as root.
		if (root == nullptr)
		{
			root = toAddNode;
		}
		else
		{
			BinarySearchTreeNode<T>* currNode = root;
			while (currNode != nullptr)
			{
				if (data < currNode->getData())
				{
					if (currNode->hasLeft())
					{
						currNode = currNode->getLeft();
					}
					else
					{
						currNode->setLeft(toAddNode);
						return;
					}						
				}
				else if (data > currNode->getData())
				{
					if (currNode->hasRight())
					{
						currNode = currNode->getRight();
					}
					else
					{
						currNode->setRight(toAddNode);
						return;
					}
				}
				else
				{
					// don't add a node with the same data value twice, just return
					return;
				}
			}
		}
	}

	BinarySearchTreeNode<T>* searchNode(const T& data, BinarySearchTreeNode<T>* currNode)
	{
		if (currNode != nullptr)
		{
			if (currNode->getData() == data)
			{
				return currNode;
			}
			else if (currNode->hasLeft() && data < currNode->getData())
			{
				return searchNode(data, currNode->getLeft());
			}
			else if (currNode->hasRight() && data > currNode->getData())
			{
				return searchNode(data, currNode->getRight());
			}
		}
		return nullptr;
	}

	BinarySearchTreeNode<T>* searchNode(const T& data)
	{
		return searchNode(data, root);
	}

	BinarySearchTreeNode<T>* DFS(const T& data, BinarySearchTreeNode<T>* currRoot)
	{
		if (currRoot != nullptr)
		{
			if (currRoot->getData() == data)
				return currRoot;

			if (currRoot->hasLeft())
			{
				auto foundLeft = DFS(data, currRoot->getLeft());
				if (foundLeft)
					return foundLeft;
			}

			if (currRoot->getRight())
			{
				auto foundRight = DFS(data, currRoot->getRight());
				if (foundRight)
					return foundRight;
			}
		}

		return nullptr;
	}

	BinarySearchTreeNode<T>* DFS(const T& data)
	{
		return DFS(data, root);
	}

private:
	BinarySearchTreeNode<T>* root;
	size_t depth;
};