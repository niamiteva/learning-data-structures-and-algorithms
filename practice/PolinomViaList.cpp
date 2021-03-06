// PolinomViaList.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>

using namespace std;

template <class T>
struct node
{
	T data;
	node<T>* next;
};

template <class T>
class LList
{
public:
	LList();
	~LList();
	LList(const LList<T>&);
	LList<T>& operator=(const LList<T>&);

	bool empty() const;
	void iterStart(node<T>* p = NULL);
	node<T>* iter();
	void toEnd(const T&);
	void insertAfter(node<T>*, const T&);
	void insertBefore(node<T>*, const T&);
	void deleteAfter(node<T>*, T&);
	void deleteBefore(node<T>*, T&);
	void deleteElem(node<T>*, T&);
	void print() const;
	int length() const;
	void concat(const LList&);
	void reverseCopy();
	void reverse();

private:
	node<T> *start, *end, *current;
	void copyList(const LList<T>&);
	void deleteList();
};

template <class T>
LList<T>::LList()
{
	start = end = NULL;
}
template <class T>
LList<T>::~LList()
{
	deleteList();
}
template <class T>
LList<T>::LList(const LList<T>& rhs)
{
	copyList(rhs);
}
template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs)
{
	if (this != &rhs)
	{
		deleteList();
		copyList(rhs);
	}
	return *this;
}
template <class T>
void LList<T>::copyList(const LList<T>& other)
{
	start = end = current = NULL;
	node<T>* p = other.start;
	while (p)
	{
		toEnd(p->data);
		p = p->next;
	}

}
template <class T>
void LList<T>::deleteList()
{
	if (empty())
	{
		cerr << "The list is empty\n";
		return ;
	}
	node<T>* p;
	while (start)
	{
		p = start;
		start = start->next;
		delete p;
	}
	end = NULL;
}
template <class T>
bool LList<T>::empty() const
{
	return start == NULL;
}
template <class T>
void LList<T>::iterStart(node<T>* p)
{
	if (p) current = p;
	else current = start;
}
template <class T>
node<T>* LList<T>::iter()
{
	node<T>* p = current;
	if (current) current = current->next;
	return p;
}
template <class T>
void LList<T>::toEnd(const T& x)
{
	current = end;
	end = new node<T>;
	end->data = x;
	end->next = NULL;
	if (current) current->next = end;
	else start = end;
}
template <class T>
void LList<T>::insertAfter(node<T>* p, const T& x)
{
	node<T> *q = new node<T>;
	q->data = x;
	q->next = p->next;
	if (p == end) end = q;
	p->next = q;
}
template <class T>
void LList<T>::insertBefore(node<T>* p, const T& x)
{
	node<T> *q = new  node<T>;
	*q = *p;
	if (p == end) end = q;
	p->data = x;
	p->next = q;
}
template <class T>
void LList<T>::deleteAfter(node<T>* p, T& x)
{
	node<T> *q = p->next;
	x = q->data;
	p->next = q->next;
	if (q == end) end = p;

	delete q;
}
template <class T>
void LList<T>::deleteElem(node<T>* p, T& x)
{
	if (p == start)
	{
		x = p->data;
		if (start == end) start = end = NULL;
		else  start = start->next;

		delete p;
	}
	else
	{
		node<T> *q = start;
		while (q->next != p) q = q->next;
		deleteAfter(q, x);
	}
}
template <class T>
void LList<T>::deleteBefore(node<T>* p, T& x)
{
	if (p != start)
	{
		node<T> *q = start;
		while (q->next != p) q = q->next;
		deleteElem(q, x);
	}
	else
	{
		cerr << "There is not elem. before p\n";
		return 0;
	} 
}
template <class T>
void LList<T>::print() const
{
	if (empty())
	{
		cerr << "The list is empty\n";
		return 0;
	}
	node<T>*p = start;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
template <class T>
int LList<T>::length() const
{
	if (empty())
	{
		cerr << "The list is empty\n";
		return 0;
	}
	int n = 0;
	node<T>* p = start;
	while (p)
	{
		n++;
		p = p->next;
	}
	return n;
}
template <class T>
void LList<T>::concat(const LList& other)
{
	node<T>* p = other.start;
	while (p)
	{
		toEnd(p->data);
		p = p->next;
	}
}
template <class T>
void LList<T>::reverseCopy()
{
	LList<T> help;
	iterStart();
	node<T> *p = iter();
	if (p)
	{
		help.toEnd(p->data);
		p = p->next;
		while (p)
		{
			help.insertBefore(help.start, p->data);
			p = p->next;
		}
	}
	*this = help;

}
template <class T>
void LList<T>::reverse()
{
	node<T> *curr, *prev, *temp;
	curr = start;
	if (curr)
	{
		prev = NULL;
		temp = start;
		start = end;
		end = start;
		while (cerr != start)
		{
			temp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = temp;
		}
		curr->next = prev;
	}
}
struct polinom
{
	double coeff;
	int pow;
};

typedef LList<polinom> poliList;

// functions with polinoms
void create(poliList& pl)
{
	char yn;
	do
	{
		polinom poli;
		cout << "coefficient(ax): ";
		cin >> poli.coeff;
		cout << "power of coefficient: ";
		cin >> poli.pow;
		pl.toEnd(poli);
		cout << "Input y/n: ";
		cin >> yn;
	} while (yn == 'y');
}
void print(poliList& pl)
{
	pl.iterStart();
	node<polinom>* p = pl.iter();
	cout << p->data.coeff << "*x^" << p->data.pow;
	p = pl.iter();
	while (p)
	{
		//positive or negative coeff
		if (p->data.coeff > 0)
			cout << " +";
		else cout << " ";

		cout << p->data.coeff << "*x^" << p->data.pow;
		p = pl.iter();
	}
	cout << endl;

}
void sumPolinoms(poliList pl1, poliList pl2, poliList& pl)
{
	pl1.iterStart(); pl2.iterStart();
	node<polinom>* p = pl1.iter();
	node<polinom>* q = pl2.iter();

	while (p && q)
	{
		if (p->data.pow > q->data.pow)
		{
			pl.toEnd(p->data);
			p = pl1.iter();
		}
		else if (p->data.pow < q->data.pow)
		{
			pl.toEnd(q->data);
			q = pl2.iter();
		}
		else
		{
			polinom poli;
			poli.coeff = p->data.coeff + q->data.coeff;
			poli.pow = p->data.pow;
			if(poli.coeff != 0) pl.toEnd(poli);
			p = pl1.iter();
			q = pl2.iter();
		}
	}

	while (p)
	{
		pl.toEnd(p->data);
		p = pl1.iter();
	}
	while (q)
	{
		pl.toEnd(q->data);
		q = pl2.iter();
	}

}
void multPolinoms(poliList pl1, poliList pl2, poliList& pl)
{
	pl1.iterStart(); pl2.iterStart();
	node<polinom>* p = pl1.iter();
	node<polinom>* q = pl2.iter();

	while (p)
	{
		while(q)
		{
			polinom poli;
			poli.coeff = p->data.coeff * q->data.coeff;
			poli.pow = p->data.pow + q->data.pow;
			pl.toEnd(poli);
			
			q = pl2.iter();
		}
		p = pl1.iter();
		pl2.iterStart();
		q = pl2.iter();
	}
}

int main()
{
	poliList pl1;
	poliList pl2;
	poliList sum;
	poliList mult;

	cout << "create poli 1:\n";
	create(pl1);
	cout << "create poli 2:\n";
	create(pl2);
	cout << endl;

	cout << "polinom 1: \n";
	print(pl1);
	cout << endl;
	cout << "polinom 2:\n";
	print(pl2);
	cout << endl;

	sumPolinoms(pl1, pl2, sum);
	cout << "sum of poli1 and poli2: \n";
	print(sum);
	cout << endl;

	multPolinoms(pl1, pl2, mult);
	cout << "multiplication of poli 1 and poli 2:\n";
	print(mult);
	cout << endl;



	return 0;
}

