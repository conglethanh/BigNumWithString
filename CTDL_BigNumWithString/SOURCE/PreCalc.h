#include "QueueLinkedList.h"
#include <vector>
#include <regex>
#include <string>
#include <fstream>

#pragma once
#define TOAN_TU 2
#define CAP_NGOAC 1
#define TOAN_HANG 0
#define ROUND_NUM 20

#define ERR_SYNTAX 10
#define ERR_NUMBER 20
#define ERR_INPUT 30

string readFile(string finp);
void standardizeString(string &s);

int priority(char c);
int priority(string c);

int isOperator(char ope);
int isOperator(string ope);

int countNumOfMaxNumber(vector<string> input);
bool checkValidExpression(string s);
bool checkNumberIsValid(string a);