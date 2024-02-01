#ifndef DYNSTACK_H
#define DYNSTACK_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>

using std::string;
using std::cout;
using std::setw;
using std::setfill;
using std::toupper;

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