/*
	Header file for the class DynStack
	which houses the necessary functions to make a dynamic stack through linked lists

	made by Luke Gegick
*/

#ifndef DYNSTACK_H
#define DYNSTACK_H

#include <string>

using std::string;

class DynStack
{
	private:
		struct stack
		{
			char* digram;
			stack* next;
		};
		stack* head;
	public:
		DynStack();
		~DynStack();
		void push(const string& digram);
		char* pop();
		bool isEmpty();
		string digramFormat(const string& digram, int& size);
		int appendDigram(stack* nodePtr, stack* newNode);
		int find(const string& digram);
		int digramDepth(const string& digram);
		int stackDepth();
		void displayStack();
		string topDigram();
};

#endif 