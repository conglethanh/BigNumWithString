#include "PolishNotation.h"

Queue ConvertToPostfix(string exp)
{
	Stack stack;
	Queue queue;
	init(stack);
	init(queue);

	string number = "";
	for (int i = 0; i < exp.length(); i++)
	{
		string s(1, exp[i]); // char => string

		if (isOperator(s) == TOAN_HANG) number += s;
		else
		{
			// Push toán hạng vào Queue
			if (number.length() > 0)
			{
				push(queue, number);
				number = "";
			}
			if (isOperator(s) == CAP_NGOAC)
			{
				if (s == "(") {
					//Xử lí số âm
					if (exp[i + 1] == '-'){
						exp.erase(i + 1, 1);
						number = "-" + number;
					}
					push(stack, "(");
				}
				else if (s == ")")
				{
					string _pop;
					pop(stack, _pop);
					// Pop dấu "(" 
					while (_pop != "(")
					{
						push(queue, _pop);
						pop(stack, _pop);
					}
				}
			}
			else//Toán tử
			{
				while (!isEmpty(stack) && priority(peek(stack)) >= priority(s))
				{
					string k;
					pop(stack, k);
					push(queue, k);
				}
				push(stack, s);
			}
		}
	}
	// Trường hợp còn sót lại toán hạng cuối cùng
	if (number.length() > 0)
	{
		push(queue, number);
		number = "";
	}
	while (!isEmpty(stack)) {
		string k;
		pop(stack, k);
		push(queue, k);
	}
	return queue;
}

string calcBigNumber(vector<string> Input){
	vector<string> stack;
	for (int i = 0; i < Input.size(); i++)
	{
		if (isOperator(Input[i]) == TOAN_HANG) stack.push_back(Input[i]);
		else//Nếu gặp toán tử
		{
			string soSau = stack.back();
			stack.pop_back();
			string soDau = stack.back();
			stack.pop_back();

			if (Input[i] == "+") stack.push_back(addFinal(soDau, soSau));
			else if (Input[i] == "-") stack.push_back(subFinal(soDau, soSau));
			else if (Input[i] == "*") stack.push_back(mulFinal(soDau, soSau));
			else if (Input[i] == "/")
			{
				if (soSau.length() > 18)
				{
					stack.push_back("0");
				}
				else
					stack.push_back(divFinal(soDau, soSau));
			}
			else if (Input[i] == "^") stack.push_back(powerFinal(soDau, soSau));
		}
	}
	string kq = stack.back();
	stack.pop_back();
	return kq;
}