#include <iostream>
#include <ostream>
#include <sstream>
#include <istream>
#include <iomanip>
#include <fstream>
#include <string>
#include "bst.h"

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::right;
using std::setfill;
using std::string;


// destructor
BST::~BST()
{
	destroy(root);
}

// destroy function
void BST::destroy(Node*& node)
{
	// deletes each node in a post order traversal
	if (node == nullptr)
	{
		return;
	}
	destroy(node->left);
	destroy(node->right);
	delete node;
	node = nullptr;
}

// insert into BST function
bool BST::insertAccount(Node*& node, string accountName)
{
	// if node doesn't exist
	if (node == nullptr)
	{
		node = new Node(accountName);
		numEntries++;
		return true;
	}

	// if account name is less than node's account name, call on node's left child
	if (accountName < node->accountName)
	{
		return insertAccount(node->left, accountName);
	}

	// if account name is greater than node's account name, call on node's right child
	if (accountName > node->accountName)
	{
		return insertAccount(node->right, accountName);
	}

	// if the accountName already exists
	if (accountName == node->accountName)
	{
		return false;
	}
	return false;
}

// public insert account
bool BST::insertAccount(string accountName)
{
	return insertAccount(root, accountName);
}

// remove from BST function
bool BST::removeAccount(Node*& node, string accountName)
{
	// runs the same comparisons as insertAccount
	if (node == nullptr)
	{
		return false;
	}
	if (accountName < node->accountName)
	{
		return removeAccount(node->left, accountName);
	}
	if (accountName > node->accountName)
	{
		return removeAccount(node->right, accountName);
	}
	if (accountName == node->accountName)
	{
		// when the correct node is found, delete based on degree
		int deg = node->degree();

		// delete the leaf
		if (deg == 0)
		{
			delete node;
			node = nullptr;
		}

		// delete the node and replace with child
		else if (deg == 1)
		{
			Node* tmp = node;
			if (node->left != nullptr)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
			delete tmp;
		}

		// find a suitable replacement, replace the node with it, reorganize tree logically
		else
		{
			Node* tmp = node->left;
			while (tmp->right != nullptr)
			{
				tmp = tmp->right;
			}
			node->accountName = tmp->accountName;
			node->firstName = tmp->firstName;
			node->lastName = tmp->lastName;
			node->gamesWon = tmp->gamesWon;
			node->gamesLost = tmp->gamesLost;
			removeAccount(node->left, tmp->accountName);
		}
		numEntries--;
		return true;
	}
	return false;
}

// public version of the remove function
bool BST::removeAccount(string accountName)
{
	return removeAccount(root, accountName);
}

// find node in BST function
bool BST::findAccount(Node* node, string accountName)
{
	// if the node doesn't exist
	if (node == nullptr)
	{
		return false;
	}

	// if the account name is less than node's account name, call on left child
	if (accountName < node->accountName)
	{
		return findAccount(node->left, accountName);
	}

	// if the account name is greater than node's account name, call on right child
	if (accountName > node->accountName)
	{
		return findAccount(node->right, accountName);
	}

	// if the account name is equal to the node's account name, return true
	if (node->accountName == accountName)
	{
		cout << node->accountName << endl;
		cout << node->lastName << ", " << node->firstName << " " << node->middleName << endl;
		cout << node->gamesWon << " Wins  " << node->gamesLost << " Losses  " << endl;
		cout << endl;
		return true;
	}
	else
	{
		return false;
	}
}

// public version of find function
bool BST::findAccount(string accountName)
{
	return findAccount(root, accountName);
}

// Edit Account function
bool BST::editNames(Node* node, string accountName, string firstName, string middleName, string lastName)
{
	// if the node doesn't exist
	if (node == nullptr)
	{
		return false;
	}

	// if the account name is less than node's account name, call on left child
	if (accountName < node->accountName)
	{
		return editNames(node->left, accountName, firstName, middleName, lastName);
	}

	// if the account name is greater than node's account name, call on right child
	if (accountName > node->accountName)
	{
		return editNames(node->right, accountName, firstName, middleName, lastName);
	}

	// if the account name is equal to the node's account name, return true
	if (node->accountName == accountName)
	{
		
		node->firstName = firstName;
		node->middleName = middleName;
		node->lastName = lastName;

		return true;
	}
	else
	{
		return false;
	}
}

// public version of edit account function
bool BST::editNames(string accountName, string firstName, string middleName, string lastName)
{
	return editNames(root, accountName, firstName, middleName, lastName);
}

// edit wins function
bool BST::editWL(Node* node, string accountName, int numGames, char indicator)
{
	// if the node doesn't exist
	if (node == nullptr)
	{
		return false;
	}

	// if the account name is less than node's account name, call on left child
	if (accountName < node->accountName)
	{
		return editWL(node->left, accountName, numGames, indicator);
	}

	// if the account name is greater than node's account name, call on right child
	if (accountName > node->accountName)
	{
		return editWL(node->right, accountName, numGames, indicator);
	}

	// if the account name is equal to the node's account name, return true
	if (node->accountName == accountName)
	{
		if (indicator == 'W')
		{

			node->gamesWon = numGames;
		}
		else if (indicator == 'L')
		{
			node->gamesLost = numGames;
		}
		else
		{
			cout << "An error has occurred. Please try again" << endl;
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

// public version of edit account function
bool BST::editWL(string accountName, int numGames, char indicator)
{
	return editWL(root, accountName, numGames, indicator);
}

// In Order Traversal function
void BST::inOrder(Node* node, ostream& os)
{
	// in case it's empty
	if (root == nullptr)
	{
		cout << "This BST is empty" << endl;
		return;
	}
	if (node == nullptr)
	{
		return;
	}

	// LNR
	inOrder(node->left, os);
	os << node->accountName << endl;
	os << node->lastName << ", " << node->firstName << " " << node->middleName << endl;
	os << node->gamesWon << " Wins  " << node->gamesLost << " Losses  " << endl;
	cout << endl;
	inOrder(node->right, os);
}

// public version of the inOrder traversal function
void BST::inOrder(ostream& os)
{
	return inOrder(root, os);
}



// Post Order Traversal Function
int BST::postOrder(Node* node, ostream& os)
{
	if (root == nullptr)
	{
		return 1;
	}
	if (node == nullptr)
	{
		return 0;
	}
	// LRN
	postOrder(node->left, os);
	postOrder(node->right, os);
	os << "Member " << node->accountName << endl;
	os << node->lastName << ", " << node->firstName << " " << node->middleName << endl;
	os << node->gamesWon << " " << node->gamesLost << " " << endl;
}

// public version of postOrder traversal function
int BST::postOrder(ostream& os)
{
	os << numEntries << " Entries" << endl;
	return postOrder(root, os);
}