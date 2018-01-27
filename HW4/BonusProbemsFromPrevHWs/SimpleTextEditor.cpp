#include <iostream>
#include <stack>
#include <string>

using namespace std;


int main()
{
	int commandCount = 0, command, k;
	string s = "", newS;
	stack<string> helper;

	cin >> commandCount;
	for (int i = 0; i < commandCount; i++)
	{
		cin >> command;
		if (command == 1)
		{
			cin >> newS;
			s += newS;
			helper.push(s);
		}
		else if (command == 2)
		{
			cin >> k; int n = s.size() - k;
			newS = "";
			for (int j = 0; j < n; j++)
			{
				newS += s[j];
			}
			s = newS;
			helper.push(s);
		}
		else if (command == 3)
		{
			cin >> k;
			cout << s[k - 1] << endl;
		}
		else if (command == 4)
		{
			helper.pop();
			if (helper.empty())
				s = "";
			else
				s = helper.top();
		}
	}



    return 0;
}

