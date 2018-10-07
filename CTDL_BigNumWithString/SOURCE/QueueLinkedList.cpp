#include "QueueLinkedList.h"

void init(Queue &q)
{
	q.head = q.tail = NULL;
}

SNode* getNode(string x)
{
	SNode*p = new SNode;
	if (p == NULL)
	{
		cout << "Not enough memory ! " << endl;
		exit(0);
	}
	p->data = x;
	p->next = NULL;
	return p;
}

bool isEmpty(Queue q)
{
	return q.head == NULL;
}

bool isFull(Queue q)
{
	return false;
}

bool push(Queue &q, string x)
{
	SNode *p = getNode(x);

	if (isEmpty(q))
	{
		q.head = q.tail = p;
	}
	else
	{
		q.tail->next = p;
		q.tail = p;
	}
	return true;
}

bool pop(Queue &q, string &x)
{
	if (isEmpty(q)) return false;

	SNode *p;
	p = q.head;
	x = p->data;
	q.head = q.head->next;
	delete p;
	return true;
}

bool peek(Queue q, string &x)
{
	if (isEmpty(q)) return false;
	x = q.head->data;
	return true;
}

void input(Queue &q)
{
	init(q);
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
		push(q, x);
	}
}

void output(Queue q)
{
	while (!isEmpty(q))
	{
		string x;
		pop(q, x);
		cout << x << "   ";
	}
}