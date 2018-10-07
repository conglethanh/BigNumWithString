#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#pragma once

struct SNode
{
	string data;
	SNode *next;
};

struct Queue
{
	SNode *head;
	SNode *tail;
};

void init(Queue &q);
SNode* getNode(string x);
bool isEmpty(Queue q);
bool isFull(Queue q);
bool push(Queue &q, string x);
bool pop(Queue &q, string &x);
bool peek(Queue q, string &x);
void input(Queue &q);
void output(Queue q);