#include "StackLinkedList.h"

void init(Stack &s)
{
	s.head = NULL;
}

bool isEmpty(Stack s)
{
	return s.head == NULL;
}

bool isFull(Stack s)
{
	return false;
}

bool push(Stack &s, string x)
{
	SNode *p = getNode(x);

	if (isEmpty(s))
	{
		s.head = p;
	}
	else
	{
		p->next = s.head;
		s.head = p;
	}
	return true;
}

bool pop(Stack &s, string &x)
{
	if (isEmpty(s)) return false;
	SNode *p;
	p = s.head;
	x = p->data;
	s.head = s.head->next;
	delete p;
	return true;
}

string peek(Stack s)
{
	if (isEmpty(s)) return "";
	return s.head->data;
}

void input(Stack &s)
{
	init(s);
	int n;
	cout << "Enter n: ";
	cin >> n;
	if (n <= 0)
	{
		cout << "N is invalid..." << endl;
		return;
	}
	for (int i = 1; i <= n; i++)
	{
		string x;
		cout << "Enter element " << i << ": ";
		cin >> x;
		push(s, x);
	}
}

void output(Stack s)
{
	while (!isEmpty(s))
	{
		string x;
		pop(s, x);
		cout << x << "   ";
	}
}