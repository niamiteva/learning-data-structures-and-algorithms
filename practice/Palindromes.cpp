// Palindromes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <queue>
#include <string.h>

using namespace std;

#define MAX 64


int main()
{
	char a[MAX];
	cin.getline(a, MAX);
	stack<char> st;
	queue<char> q;
	bool palindrome = false;
	for (int i = 0; i < strlen(a); i++)
	{
		st.push(a[i]);
		q.push(a[i]);
	}
	while (!st.empty())
	{
		if (st.top() == q.front())
			palindrome = true;
		else
		{
			palindrome = false;
			break;
		}
		st.pop();
		q.pop();
	}

	if (palindrome) cout << "The word , " << a << " , is a palindrome" << endl;
	else cout << "The word," << a << ", is not a palindrome" << endl;


    return 0;
}

