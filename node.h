#pragma once
#include <string>
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using std::string;
using std::ostream;


class Node
{
public:
	string accountName;
	string firstName;
	string middleName;
	string lastName;
	int gamesWon;
	int gamesLost;
	Node* left;
	Node* right;

	Node() : accountName(""), firstName(""), middleName(""), lastName(""), gamesWon(0), gamesLost(0), left(nullptr), right(nullptr) {}
	Node(string accountName) : accountName(accountName), firstName(""), middleName(""), lastName(""), gamesWon(0), gamesLost(0), left(nullptr), right(nullptr) {}
	Node(string accountName, string firtstName, string middleName, string lastName, int gamesWon, int gamesLost) : accountName(accountName), firstName(firstName), middleName(middleName), lastName(lastName), gamesWon(gamesWon), gamesLost(gamesLost), left(nullptr), right(nullptr) {}
	Node(string accountName, string firtstName, string lastName, int gamesWon, int gamesLost) : accountName(accountName), firstName(firstName), middleName(""), lastName(lastName), gamesWon(gamesWon), gamesLost(gamesLost), left(nullptr), right(nullptr) {}


	// finds the degree of a particular node
	int degree() const
	{
		if (left == nullptr && right == nullptr)
		{
			return 0;
		}
		else if (left != nullptr && right == nullptr)
		{
			return 1;
		}
		else if (left == nullptr && right != nullptr)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
};