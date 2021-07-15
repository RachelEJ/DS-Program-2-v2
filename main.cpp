#include <iostream>
#include <ostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include "Tokenizer.h"
#include "bst.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ofstream;
using std::stringstream;

// Function that saves the  BST into a file
void saveDirectory(BST& memDirectory, ofstream& of, string fileName)
{
	of.open(fileName);
	if (of.is_open())
	{
		if (memDirectory.postOrder(of) == 1)
		{
			cout << "This BST is empty and " << fileName << " has not been saved" << endl << endl;
		}
		else
		{
			cout << "BST successfully saved into " << fileName << endl << endl;
		}
	}
	else
	{
		cout << "Failed to open the file" << endl;
	}
	of.close();
}

bool processText(istream& is, BST& memDirectory, bool interactive = true)
{
	// implement support for 
	// exit ... exit the program
	// add string string ... concatenate two strings
	// add double double ... sum two integers
	// load file ... loads a file containing supported commands
	string line;
	string command;
	string arg1, arg2, arg3, arg4, arg5;
	int intArg;
	Tokenizer tkn;
	int numEntries = 0;
	while (true)
	{
		if (!interactive)
		{
			if (is.eof()) return true;
		}
		else { cout << ">> "; }

		getline(is, line);
		tkn.setString(line);

		tkn.readWord(command);

		// exits program
		if (command == "exit")
		{
			cout << "Exiting ...." << endl;
			return false;
		}

		// load command
		if (command == "load")
		{
			// load expects a filename .. so read one more word
			if (!tkn.readWord(arg1)) {
				cout << "Missing file name" << endl;
				continue; // skip back to the top of the read loop
			}
			ifstream fin;
			bool status = true;
			fin.open(arg1);
			if (fin.is_open())
			{
				status = processText(fin, memDirectory, false);
			}
			else { cout << "Failed to open the file" << endl; }
			fin.close();
			if (!status) return false;
		}

		// save bst command
		if (command == "save")
		{
			if (!tkn.readWord(arg1))
			{
				cout << "You need to specify a file name to save this directory" << endl << endl;
			}
			else
			{
				ofstream of;
				saveDirectory(memDirectory, of, arg1);
			}

		}

		// display bst command
		if (command == "directory")
		{
			memDirectory.inOrder(cout);
			cout << endl;
		}

		// display member info command
		if (command == "display")
		{
			if (!tkn.readWord(arg1))
			{
				cout << "You must enter a member's account name to display their info" << endl;
			}
			else
			{
				memDirectory.findAccount(arg1);
			}
		}

		// clear directory command
		if (command == "clear")
		{
			memDirectory.~BST();
			cout << "The directory has been cleared" << endl << endl;;
		}

		// add member command
		if (command == "add")
		{
			if (!tkn.readWord(arg1))
			{
				cout << "You must enter an account name to add a member" << endl << endl;
			}
			else
			{
				if (memDirectory.insertAccount(arg1) == false)
				{
					cout << "A user with that account name already exists. Please choose another account name";
				}
				else
				{
					cout << "Account with name " << arg1 << " has been created!" << endl << endl;
				}
			}
		}

		if (command == "set")
		{
			if (!tkn.readWord(arg1))
			{
				cout << "You must enter an account name to set a member's info!" << endl << endl;
			}
			else
			{
				if (!tkn.readWord(arg2))
				{
					cout << "You must enter \"name,\" \"wins,\" or \"losses\" to set a user's name, wins, or losses!" << endl << endl;
				}
				else
				{
					if (arg2 == "name")
					{
						if (!tkn.readWord(arg3))
						{
							cout << "You must enter a first name to edit this member's info" << endl << endl;
						}
						else
						{
							if (!tkn.readWord(arg4))
							{
								cout << "You must either enter a middle or last name to edit this member's info" << endl << endl;
							}
							else
							{
								// edit only first and last name
								if (!tkn.readWord(arg5))
								{
									if (memDirectory.editNames(arg1, arg3, "", arg4) == false)
									{
										cout << "That account name doesn't exist" << endl << endl;
									}
									else
									{
										cout << arg1 << "'s name has been updated!" << endl << endl;
									}
								}
								// edit all 3 names
								else
								{
									if (memDirectory.editNames(arg1, arg3, arg4, arg5) == false)
									{
										cout << "That account name doesn't exist" << endl << endl;
									}
									else
									{
										cout << arg1 << "'s name has been updated!" << endl << endl;
									}
								}
							}
						}
					}
					else if (arg2 == "wins")
					{
						if (!tkn.readInteger(intArg))
						{
							cout << "You must enter a number to edit this member's wins" << endl << endl;
							continue;
						}
						else
						{
							if (memDirectory.editWL(arg1, intArg, 'W') == false)
							{
								cout << "That account name doesn't exist" << endl << endl;
							}
							else
							{
								cout << arg1 << "'s win count has been updated!" << endl << endl;
							}
						}
					}
					else if (arg2 == "losses")
					{
						if (!tkn.readInteger(intArg))
						{
							cout << "You must enter a number to edit this member's losses" << endl << endl;
							continue;
						}
						else
						{
							if (memDirectory.editWL(arg1, intArg, 'L') == false)
							{
								cout << "That account name doesn't exist" << endl << endl;
							}
							else
							{
								cout << arg1 << "'s loss count has been updated!" << endl << endl;
							}
						}
					}
					else
					{
						cout << "That is not a valid command. Please try again" << endl << endl;
					}
				}
			}
		}

		// remove account function
		if (command == "remove")
		{
			if (!tkn.readWord(arg1))
			{
				cout << "You must specify a member account to remove" << endl << endl;
			}
			else
			{
				if (memDirectory.removeAccount(arg1) == false)
				{
					cout << "That account doesn't exist. Please try again" << endl << endl;
				}
				else
				{
					cout << "Account named " << arg1 << " was successfully removed!" << endl << endl;
				}
			}
		}
	}
}


int main()
{
	BST memDirectory;
	processText(cin, memDirectory);
	return 0;

}