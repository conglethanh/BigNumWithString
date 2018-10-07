#include "PreCalc.h"
#pragma once

int countNumAfterDot(string a);

void fixed(string &a, string &b);
void fixed(string& a, string src, string dest);
bool isNegative(string a);

string add(string a, string b);
string sub(string a, string b);
string mul(string a, string b);
string longDivision(string number, long long  divisor);
string powerBig(string number, int power);

string addBigReal(string a, string b);
string subBigReal(string a, string b);
string mulBigReal(string a, string b);
string addFinal(string a, string b);

string subFinal(string a, string b);
string mulFinal(string a, string b);
string powerFinal(string a, string power);

string divDotDecimal(string number, string divisor);
string divBigReal(string number, string divisor);
string divFinal(string a, string b);

string roundBigNum(string &a);