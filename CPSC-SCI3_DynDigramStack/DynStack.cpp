/*
	Implementation file for the Dynstack class

	made by Luke Gegick
*/

#include "DynStack.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

using std::cout;
using std::setw;
using std::setfill;
using std::toupper;
using std::setw;
using std::setfill;

DynStack::DynStack()
{
	head = nullptr;
}

DynStack::~DynStack()
{
	stack* nodePtr;
	stack* nextPtr;
	nodePtr = head;
	if (head)
	{
		while (nodePtr != nullptr)
		{
			nextPtr = nodePtr->next;
			delete nodePtr;
			nodePtr = nextPtr;
		}
	}
}

void DynStack::push(const string& digram)
{
	stack* nodePtr;

	//create a string with the characters seperated
	string strDigram = digram;
	int stringSize = strDigram.size();
	strDigram = digramFormat(digram, stringSize);
	int stringIndex = 0;

	//error case or case of null handling
	if (strDigram == "")
	{
		std::cerr << "Err: Only sent in punctuation, skipping push";
		return;
	}

	//initialize the first struct
	stack* newStack = new stack;
	newStack->digram = new char[3];
	newStack->digram[0] = strDigram[stringIndex++];
	newStack->digram[1] = strDigram[stringIndex++];
	newStack->digram[2] = ' ';

	//check if head node exists before initializing the rest 
	// of the digrams
	if (!head)
	{
		head = newStack;
		head->next = nullptr;
	}
	nodePtr = head; //index of the stack

	//if head does not exist, then append it to the stack
	appendDigram(nodePtr, newStack);

	//need to make an array of stack pointers
	int digramTotal = digramDepth(digram) - 1; // -1 removes the above digram added into newStack
	if (digramTotal == 0)
	{
		return;
	}
	stack** newStacks = new stack*[digramTotal];
	int stackIncrement = 0;

	//initialize the rest of the digrams
	while (strDigram[stringIndex] != '~')
	{ 
		
		//initialize temp digram
		char* temp = new char[3];
		temp[0] = strDigram[stringIndex++];
		temp[1] = strDigram[stringIndex++];
		temp[2] = ' ';

		//check if the digram is in the stack (use a seperate function)
		int isFound = find(temp);

		if (isFound == 0)
		{
			//add the digram to the list
			newStacks[0] = new stack;
			newStacks[0]->digram = temp;
			newStacks[0]->next = nullptr;

			//append the digram to the end of the list
			int appendStatus = appendDigram(nodePtr, newStacks[0]);
			stackIncrement = stackIncrement + 1;
			if (appendStatus != 1)
				std::cerr << "Err: Append error, nodePtr is uninitialized to head\n";
		} 
	} 
}


char* DynStack::pop()
{
	stack* nodePtr;
	stack* previousNode;
	char* rtnValue = new char[3];
	rtnValue[0] = '~'; //if an error occurs, send this back
	if (!head)
	{
		std::cerr << "Err: no node to pop\n";
		std::exit(1);
	}
	else
	{
		nodePtr = head;
		previousNode = nullptr;
		
		while (nodePtr->next != nullptr)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (previousNode == nullptr) //the head node is only one in list
		{
			rtnValue = nodePtr->digram;
			head = nullptr;
			return rtnValue;
		}
		else
		{
			rtnValue = nodePtr->digram;
			previousNode->next = nullptr;
			return rtnValue;
		}
	}
	return rtnValue; //if an error occurs
}

int DynStack::digramDepth(const string& digram)
{
	int digramSize = digram.size();
	int digramCount = (digramSize / 2) + 1;
	return digramCount;
}

void DynStack::displayStack()
{
	stack* nodePtr;
	if (!head)
	{
		//display an empty table
		cout << "Contents of the Stack include: \n";
		cout << "Stack Index" << setw(5) << setfill(' ')
			<< "|" << setw(15) << setfill(' ') << "Index Value" << '\n';
	}
	else
	{
		nodePtr = head;

		//display the table header
		cout << "Stack Index" << setw(5) << setfill(' ')
			<< "|" << setw(15) << setfill(' ') << "Index Value" << '\n';
		int listIncrement(0);
		while (nodePtr != nullptr)
		{
			char displayAssist;
			if (nodePtr->digram[1] == ' ') //shows spaces as _ for readability
			{
				displayAssist = '_';
			}
			else
			{
				displayAssist = nodePtr->digram[1];
			}
			//show the values in the stack
			cout << setw(7) << listIncrement++ << setw(9) << setfill(' ') <<
				"|" << setw(10) << setfill(' ') << nodePtr->digram[0] << displayAssist
				<< nodePtr->digram[2] << "\n";
			nodePtr = nodePtr->next;
		}
		cout << "\n\n";
	}
}

int DynStack::stackDepth()
{
	stack* nodePtr;
	int Depth(0);

	if (!head)
	{
		return 0;
	}
	else
	{
		nodePtr = head;
		while (nodePtr != nullptr)
		{
			Depth++;
			nodePtr = nodePtr->next;
		}
	}
	return Depth;
}

int DynStack::appendDigram(stack* nodePtr, stack* newNode)
{
	if (nodePtr != nullptr)
	{
		//nodePtr is assumed to be initialized to head
		while (nodePtr->next != nullptr)
		{
			nodePtr = nodePtr->next;
		}
		nodePtr->next = newNode;
		nodePtr->next->next = nullptr;
		return 1; //append correctly
	}
	else
		return 0; //error case
}

string DynStack::digramFormat(const string& digram, int& size)
{
	//if user pushes an empty string
	if (size == 0)
	{
		std::cerr << "Err: Empty string presented to stack, Fatal Error\n";
		std::exit(1);
	}
	else if (size == 1) //if string is only one char long
	{
		string newStr = digram;
		string pause;
		if (ispunct(newStr[0]))
		{
			return("");
		}
		else
			newStr[0] = toupper(digram[0]);
		newStr += ' ';
		size = 2;
		return newStr;
	}
	if (size % 2 == 1) //if the input is an odd number of letters
	{ 
		//add a space to the end( Hello is HE_LL_O__)
		string temp = digram.substr(0, size);
		
		//make all chars uppercase, change punct to <sp>
		for (int i = 0; i <= size; i++)
		{
			if (ispunct(temp[i]))
				temp[i] = ' ';
			else
				temp[i] = toupper(temp[i]);
		}

		temp += ' ';
		temp += '~';
		size = temp.size();
		return temp;
	}
	else
	{
		//if the digram is even, dont add _ just ~
		//also check for punct, and change punct to <sp>
		string temp = digram;
		for (int i = 0; i <= size; i++)
		{
			if (ispunct(temp[i]))
				temp[i] = ' ';
			else 
				temp[i] = toupper(temp[i]);
		}

		temp += '~';
		size = temp.size();
		return temp;
	}
}

int DynStack::find(const string& digram)
{
	stack* nodePtr;
	if (!head)
	{
		return 0; //0 implies digram not found
	}
	else
	{
		nodePtr = head;
		while (nodePtr != nullptr)
		{
			if (nodePtr->digram[0] == digram[0] && nodePtr->digram[1] == digram[1])
			{
				return 1; //if its a match, return 1 as success
			}
			else
			{
				nodePtr = nodePtr->next;
			}
		}
		return 0; //if not successful, return 0
	}
}

bool DynStack::isEmpty()
{
	if (!head)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string DynStack::topDigram()
{
	stack* nodePtr;
	string rtnStr;
	if (!head)
	{
		std::cerr << "No digram on top since stack is empty\n";
		return("");
	}
	else
	{
		nodePtr = head;
		while (nodePtr->next != nullptr)
		{
			nodePtr = nodePtr->next;
		}
		//nodePtr points to the last struct in the stack
		rtnStr += nodePtr->digram[0];
		rtnStr += nodePtr->digram[1];
		rtnStr += nodePtr->digram[2];
		return rtnStr;
	}
}