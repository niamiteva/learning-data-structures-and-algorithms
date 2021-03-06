﻿
// LStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* next;
};
template <class T>
class LStack
{
public:
	LStack();
	~LStack();
	LStack(const LStack<T>&);
	LStack<T>& operator=(const LStack<T>&);

	bool empty() const;
	void push(const T&);
	T top() const;
	T pop();
	int length();

private:
	Node<T> * start;
	void copyStack(const LStack &);
	void deleteStack();
};
template <class T>
LStack<T>::LStack() : start(NULL) {}
template <class T>
LStack<T>::~LStack()
{
	deleteStack();
}
template <class T>
LStack<T>::LStack(const LStack<T>& rhs)
{
	copyStack(rhs);
}
template <class T>
LStack<T>& LStack<T>::operator=(const LStack<T>& rhs)
{
	if (this != &rhs)
	{
		deleteStack();
		copyStack(rhs);
	}
	return *this;
}
template <class T>
void LStack<T>::copyStack(const LStack& other)
{
	if (other.start)
	{
		Node<T> *p = other.start, *q = NULL, *s = NULL;
		start = new Node<T>;
		strat->data = p->data;
		start->next = q;
		p = p->next;
		while (p)
		{
			s = new Node<T>;
			s->data = p->data;
			q->next = s;
			q = s;
			p = p->next;
		}
		q->next = NULL;
	}
	else start = NULL;

}
template <class T>
void LStack<T>::deleteStack()
{
	while (!empty()) pop();
}
template <class T>
bool LStack<T>::empty() const
{
	return start == NULL;
}
template <class T>
void LStack<T>::push(const T& x)
{
	Node<T>* p = start;
	start = new Node<T>;
	start->data = x;
	start->next = p;
}
template <class T>
T LStack<T>::top() const
{
	if (empty())
	{
		cerr << "The stack is empty\n";
		return 0;
	}
	T x = start->data;
	return x;
}
template <class T>
T LStack<T>::pop()
{
	if (empty())
	{
		cerr << "The stack is empty\n";
		return 0;
	}
	Node<T>* p;
	p = start;
	T x = p->data;
	start = start->next;
	delete p;

	return x;
}
template <class T>
int LStack<T>::length()
{
	if (empty())
	{
		cerr << "The stack is empty\n";
		return 0;
	}
	Node<T> *p = start;
	int len = 0;
	while (p)
	{
		p = p->next;
		len++;
	}
}
#define MAX 256

int main()
{
	/*
	! -> deletes one letter
	# -> deletes all letter before #
	*/
	LStack<char> help;
	LStack<char> st;
	char a[MAX];
	cin.getline(a, MAX);
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] >= 'a' && a[i] <= 'z')
		{
			help.push(a[i]);
		}
		else if (a[i] == '!')
		{
			help.pop();
		}
		else if (a[i] == '#')
		{
			while (!help.empty())
				help.pop();
		}
	}
	if (!help.empty())
	{
		while (!help.empty())
		{
			st.push(help.top());
			help.pop();
		}
		while (!st.empty())
		{
			cout << st.top();
			st.pop();
		}
	}
	else
		cout << "Empty string";
	cout << endl;


    return 0;
}

