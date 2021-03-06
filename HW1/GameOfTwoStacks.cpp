
#include <iostream>


using namespace std;

template <typename T>
struct node 
{
	T data;
	node* next;
};
template <typename T>
class LStack 
{
private:
	node<T>* topNode;
	void copy(node<T>* toCopy);
	void eraseStack();
	void copyStack(LStack const&);

public:
	LStack(); // създаване на празен стек
	LStack(LStack const&); // Конструктор за копиране
	LStack& operator=(LStack const&); // операция за присвояване
	~LStack(); // деструктор
	bool empty() const;
	void push(T const& x);
	T pop();
	T top() const;
};
template <typename T>
LStack<T>::LStack() : topNode(nullptr) {}
template <typename T>
bool LStack<T>::empty() const 
{
	return topNode == nullptr;
}
template <typename T>
void LStack<T>::push(T const& x) 
{
	node<T>* p = new node<T>;
	p->data = x;
	p->next = topNode;
	topNode = p;
}
template <typename T>
T LStack<T>::pop() 
{
	if (empty()) 
	{
		cerr << "празен стек!\n";
		return 0;
	}
	node<T>* p = topNode;
	topNode = topNode->next;
	T x = p->data;
	delete p;
	return x;
}
template <typename T>
T LStack<T>::top() const 
{
	if (empty()) 
	{
		cerr << "празен стек!\n";
		return 0;
	}
	return topNode->data;
}
template <typename T>
void LStack<T>::eraseStack() 
{
	while (!empty())
		pop();
}
template <typename T>
LStack<T>::~LStack() 
{
	eraseStack();
}
template <typename T>
void LStack<T>::copy(node<T>* toCopy) 
{
	if (toCopy == nullptr)
		return;
	copy(toCopy->next);
	push(toCopy->data); //добавямe първия елемент отгоре
}
template <typename T>
void LStack<T>::copyStack(LStack const& ls) 
{
	topNode = nullptr;
	copy(ls.topNode);
}
template <typename T>
LStack<T>::LStack(LStack const& ls) 
{
	copyStack(ls);
}
template <typename T>
LStack<T>& LStack<T>::operator=(LStack const& ls)
{
	if (this != &ls) {
		eraseStack();
		copyStack(ls);
	}
	return *this;
}

int main()
{
	int games;
	cin >> games;
	for (int g = 0; g < games; g++)
	{
		int n, m, x;
		cin >> n >> m >> x;
		LStack<int> helpA;
		LStack<int> a;
		LStack<int> helpB;
		LStack<int> b;
		LStack<int> help;
		int number, sum = 0, score=0;
		for (int i = 0; i < n; i++)
		{
			cin >> number;
			helpA.push(number);
			help.push(helpA.top());
		}
		for (int i = 0; i < m; i++)
		{
			cin >> number;
			helpB.push(number);
		}
		for (int i = 0; i < n; i++)
		{
			a.push(helpA.top());
			helpA.pop();
		}
		for (int i = 0; i < m; i++)
		{
			b.push(helpB.top());
			helpB.pop();
		}

		if (n >= m)
		{
			for (int i = 0; i < n; i++)
			{
				if (i % 2 == 0)
				{
					sum += a.top();
					a.pop();
				}
				else
				{
					if (b.empty())
					{
						sum += a.top();
						a.pop();
					}
					else
					{
						sum += b.top();
						b.pop();
					}
				}
				if (sum > x)
				{
					score = i;
					break;
				}
			}
		}
		else if (n < m)
		{
			for (int i = 0; i < m; i++)
			{
				if (i % 2 == 0)
				{
					sum += b.top();
					b.pop();
				}
				else
				{
					if (a.empty())
					{
						sum += b.top();
						b.pop();
					}
					else
					{
						sum += a.top();
						a.pop();
					}
				}
				if (sum > x)
				{
					score = i;
					break;
				}
			}
		}
		else if (m == 0)
		{
			for (int i = 0; i < n; i++)
			{				
				sum += a.top();
				a.pop();
				if (sum > x)
				{
					score = i;
					break;
				}
			}
		}
		else if (n == 0)
		{
			for (int i = 0; i < m; i++)
			{
				sum += b.top();
				b.pop();
				if (sum > x)
				{
					score = i;
					break;
				}
			}
		}
		cout << score << endl;
	}

    return 0;
}

