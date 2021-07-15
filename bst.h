#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include "node.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;


class BST
{
private:
	Node* root;
	int numEntries;
	bool insertAccount(Node*& node, string accountName);
	bool removeAccount(Node*& node, string accountName);
	bool findAccount(Node* node, string accountName);
	bool editNames(Node* node, string accountName, string firstName, string middleName, string lastName);
	bool editWL(Node* node, string accountName, int numGames, char indicator);
	void inOrder(Node* node, ostream& os);
	int postOrder(Node* node, ostream& os);
	void destroy(Node*& node);

public:
	BST() : root(nullptr) {}
	~BST();
	bool insertAccount(string accountName);
	bool removeAccount(string accountName);
	bool findAccount(string accountName);
	bool editNames(string accountName, string firstName, string middleName, string lastName);
	bool editWL(string accountName, int numGames, char indicator);
	void inOrder(ostream& os);
	int postOrder(ostream& os);
};