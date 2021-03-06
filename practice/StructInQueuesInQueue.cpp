// StructInQueuesInQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

//#define NAME 100

struct person
{
	string name;
	int age;
	bool operator==(const person& p) const
	{
		return name == p.name;
	}
	bool operator<(const person& p)const
	{
		return name < p.name;
	}
};

typedef queue<person> personQ;
typedef queue<personQ> perQQ;

void printQQ(perQQ qq)
{
	while (!qq.empty())
	{
		while (!qq.front().empty())
		{
			cout << qq.front().front().name << " , "<< qq.front().front().age<<endl;
			qq.front().pop();
		}
		cout << endl;
		qq.pop();
	}
}
personQ merge(perQQ qq)
{
	personQ merged;
	while (!qq.empty())
	{
		while (!qq.front().empty())
		{
			person p;
			p.name = qq.front().front().name;
			p.age = qq.front().front().age;
			merged.push(p);
			qq.front().pop();
		}
		qq.pop();
	}
	return merged;
}
void printQ(personQ merged)
{
	while (!merged.empty())
	{
		cout << merged.front().name << " ,  " << merged.front().age << endl;
		merged.pop();
	}
}

int main()
{
	perQQ qq;
	int n; cout << "n -> number of queues: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		personQ q;
		int m = 0; cout << "m -> number of people in queue: "; cin >> m;
		for (int j = 0; j < m; j++)
		{
			person s;
			cout << "Name: ";
			cin >> s.name;
			cout << "Age:";
			cin >> s.age;
			q.push(s);
		}
		qq.push(q);
	}
	cout << endl;
	printQQ(qq);

	perQQ sorted;
	personQ merged;
	merged = merge(qq);
	printQ(merged);
	



    return 0;
}

