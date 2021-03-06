// PolinomCalcDList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template <class T>
struct node
{
	T data;
	node<T> *next, *prev;
};

template <class T>
class DList
{
public:
	DList();
	~DList();
	DList(const DList<T>&);
	DList<T>& operator=(const DList<T>&);

	bool empty() const;
	void iterStart(node<T> *p = NULL);
	void iterEnd(node<T> *p = NULL);
	node<T>* iterNext();
	node<T>* iterPrev();
	void toEnd(const T&);
	void toStart(const T&);
	void deleteElem(node<T> *, T&);
	void print() const;
	void printReverse() const;
	int length() const;
	void reverseDList();


private:
	node<T> *start, *end, *currentS, *currentE;
	void deleteList();
	void copyList(const DList<T>&);
};

template <class T>
DList<T>::DList()
{
	start = NULL;
	end = NULL;
}
template <class T>
DList<T>::~DList()
{
	deleteList();
}
template <class T>
DList<T>::DList(const DList<T>& list)
{
	copyList(list);
}
template <class T>
DList<T>& DList<T>::operator=(const DList<T>& list)
{
	if (this != &list)
	{
		deleteList();
		copyList(list);
	}
	return *this;
}
template <class T>
void DList<T>::deleteList()
{
	node<T> *p;
	while (start)
	{
		p = start;
		start = start->next;
		delete p;
	}
}
template <class T>
void DList<T>::copyList(const DList<T>& list)
{
	start = end = NULL;
	if (list.start)
	{
		node<T>*p = list.start;
		while (p)
		{
			toEnd(p->data);
			p = p->next;
		}
	}
}
template <class T>
bool DList<T>::empty() const
{
	return start == NULL
}
template <class T>
void DList<T>::iterStart(node<T> *p)
{
	if (p) currentS = p;
	else currentS = start;
}
template <class T>
void DList<T>::iterEnd(node<T> *p)
{
	if (p) currentE = p;
	else currentE = end;
}
template <class T>
node<T>* DList<T>::iterNext()
{
	node<T> *p = currentS;
	if (currentS) currentS = currentS->next;
	return p;
}
template <class T>
node<T>* DList<T>::iterPrev()
{
	node<T> *p = currentE;
	if (currentE) currentE = currentE->prev;
	return p;
}
template <class T>
void DList<T>::toEnd(const T& x)
{
	node<T> *p = end;
	end = new node<T>;
	end->data = x;
	end->next = NULL;
	if (p) p->next = end;
	else start = end;
	end->prev = p;
}
template <class T>
void DList<T>::toStart(const T& x)
{
	node<T>* p = start;
	start = new node<T>;
	start->data = x;
	start->prev = NULL;
	if (p) p->prev = start;
	else end = start;
	start->next = p;
}
template <class T>
void DList<T>::deleteElem(node<T> *p, T& x)
{
	x = p->data;
	if (start == end)
	{
		start = NULL;
		end = NULL;
	}
	else if (p == start)
	{
		start = start->next;
		start->prev = NULL;
	}
	else if (p == end)
	{
		end = end->prev;
		end->next = NULL;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	delete p;
}
template <class T>
void DList<T>::print() const
{
	node<T> *p = start;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
template <class T>
void DList<T>::printReverse() const
{
	node<T> *p = end;
	while (p)
	{
		cout << p->prev << " ";
		p = p->prev;
	}
	cout << end;
}
template <class T>
int DList<T>::length() const
{
	node<T> *p = start;
	int n = 0;
	while (p)
	{
		n++;
		p = p->next;
	}
	return n;
}

void createList(int n, DList<int>& list)
{
	for (int i = 0; i < 2 * n; i++)
	{
		cout << ">";
		int x; cin >> x;
		list.toEnd(x);
	}
}
int sum(DList<int>& list)
{
	list.iterStart();
	node<int> *p = list.iterNext();
	list.iterEnd();
	node<int> *q = list.iterPrev();
	int sum = 0;
	//sum = sum + (p->data*p->data);
	int n = list.length() / 2;
	for (int i = 0; i < n; i++)
	{
		sum = sum + (p->data*q->data);
		p = list.iterNext();
		q = list.iterPrev();
	}

	return sum;
}

int maximin(DList<int>& list)
{
	int max = -1000;
	list.iterStart();
	node<int>* p = list.iterNext();
	list.iterEnd();
	node<int>* q = list.iterPrev();
	int n = list.length() / 2;
	for (int i = 0; i < n; i++)
	{
		if (p->data >= q->data)
		{
			if (q->data >= max)
				max = q->data;
		}
		else
		{
			if (p->data >= max)
				max = p->data;
		}
		p = p->next;
		q = q->prev;
	}

	return max;

}

int main()
{
	DList<int> list;
	int n = 0; cin >> n;
	createList(n, list);
	list.print();
	cout << "sum = " << sum(list) << endl;
	cout << "maximin = " << maximin(list) << endl;


    return 0;
}

