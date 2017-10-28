// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<new>
#include<memory>
#include<vector>


using namespace std;


class TreeNode
{
public:
	TreeNode() : count(0) {}
	TreeNode(const TreeNode &x); //value(x.value), count(x.count), left(new TreeNode(*x.left)), right(new TreeNode(*x.right)) {}
	TreeNode &operator=(const TreeNode &x);
	~TreeNode();
	int value_return();
	TreeNode left_return();
private:
	std::string value;
	int count;
	TreeNode *left;
	TreeNode *right;
};


TreeNode::TreeNode(const TreeNode &x) : value(x.value), count(x.count), 
	left(new TreeNode(*x.left)), right(new TreeNode(*x.right)) {}

TreeNode &TreeNode::operator=(const TreeNode &x)
{
	auto yleft = new TreeNode(*x.left);
	auto yright = new TreeNode(*x.right);
	delete left;
	delete right;
	value = x.value; count = x.count; left = yleft; right = yright;
	return *this;
}

TreeNode :: ~TreeNode()
{
	delete left; delete right;
}

int TreeNode::value_return() {
	return count;
}

TreeNode TreeNode::left_return()
{
	return *left;
}


class BinStrTree
{
private:
TreeNode *root;
};


int main()
{
	

    return 0;
}



