#include "QueueLinkedList.h"
#pragma once

struct Stack
{
	SNode *head;
};

void init(Stack &s);
bool isEmpty(Stack s);
bool isFull(Stack s);
bool push(Stack &s, string x);
bool pop(Stack &s, string &x);
string peek(Stack s);
void input(Stack &s);
void output(Stack s);