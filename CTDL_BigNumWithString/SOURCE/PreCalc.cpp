#include "PreCalc.h"

string readFile(string finp){
	ifstream fi(finp);
	if (!fi)
	{
		throw ERR_INPUT;
	}
	string s;
	while (!fi.eof()){
		string k;
		getline(fi, k);
		s = s + k;
	}
	fi.close();
	return s;
}

void standardizeString(string &s){
	for (int i = 0; i < s.length(); i++){
		if (s[i] == ' ' || s[i] == '\n'){
			s.erase(i, 1);
			i--;
		}
	}
}

int priority(char c){
	if (c == '+')
		return 1;
	else if (c == '-')
		return 2;
	else if (c == '*')
		return 3;
	else if (c == '/')
		return 4;
	else if (c == '^')
		return 5;
	else
		return 0;
}

int priority(string c){
	if (c == "+")
		return 1;
	else if (c == "-")
		return 2;
	else if (c == "*")
		return 3;
	else if (c == "/")
		return 4;
	else if (c == "^")
		return 5;
	else
		return 0;
}

int isOperator(char ope)
{
	if (priority(ope) == 0)
	{
		if (ope != '(' && ope != ')') return TOAN_HANG;
		else return CAP_NGOAC;
	}
	return TOAN_TU;
}

int isOperator(string ope)
{
	if (priority(ope) == 0)
	{
		if (ope != "(" && ope != ")") return TOAN_HANG;
		else return CAP_NGOAC;
	}
	return TOAN_TU;
}

int countNumOfMaxNumber(vector<string> input){
	int maxCount = input[0].length();
	for (int i = 1; i < input.size(); i++){
		int k = input[i].length();
		if (maxCount < k){
			maxCount = k;
		}
	}
	return maxCount;
}

bool checkValidExpression(string s){
	//Vị trí cuối chuỗi
	if (s[s.length() - 1] == '(' || isOperator(s[s.length() - 1]) == TOAN_TU || s[s.length() - 1] == '.')
		return false;
	//Vị trí đầu chuỗi
	if (s[0] == ')' || ((s[0]<'0' || s[0]>'9') && s[0] != '('))
		return false;
	int soNgoacMo = 0;
	int soNgoacDong = 0;
	for (int i = 0; i < s.length(); i++){
		//Kí tự và toán tử ko hợp lệ nằm ngoài 0..9 + - * / ^
		if (s[i] != '+'&&s[i] != '-'&& s[i] != '*'&&s[i] != '/'&&s[i] != '^'
			&&s[i] != '('&&s[i] != ')'&&s[i] != '.'&&s[i] != ' ' && (s[i]<'0' || s[i]>'9'))
			return false;
		// dấu (+ hoặc ()
		if (s[i] == '(' &&i + 1 < s.length() && isOperator(s[i + 1]) == TOAN_TU&&s[i + 1] != '-'){
			return  false;
		}
		if (s[i] == '(' &&i + 1 < s.length() && s[i + 1] == ')'){
			return  false;
		}
		// toán tử +-*/^ gặp )
		if (isOperator(s[i]) == TOAN_TU&&i + 1 < s.length() && s[i + 1] == ')'){
			return false;
		}
		// toán tử +-*/^ gặp toán tử
		if (isOperator(s[i]) == TOAN_TU&&i + 1 < s.length() && isOperator(s[i + 1]) == TOAN_TU){
			return false;
		}
		//cặp ngoặc gặp cặp ngoặc ) (
		if (s[i] == ')'&&i + 1 < s.length() && s[i + 1] == '('){
			return false;
		}
		//Số hạng gặp dấu ngoặc vd: 7(8 hoặc 7)8 
		if ((isOperator(s[i]) == TOAN_HANG&&i + 1 < s.length() && s[i + 1] == '(')
			|| (isOperator(s[i + 1]) == TOAN_HANG&&i + 1 < s.length() && s[i] == ')'))
			return false;
		if (s[i] == '(')
			soNgoacMo++;
		if (s[i] == ')')
			soNgoacDong++;
	}
	if (soNgoacMo != soNgoacDong)
		return false;

	return true;
}

bool checkNumberIsValid(string a)
{
	int c = 0;
	int k = a.find('.');
	while (k != -1){
		if (k == 0 || k == a.length() - 1)
			return false;
		c++;
		k = a.find('.', k + 1);
	}
	if (c > 1)
		return false;
	if (a.find('(') != -1 || a.find(')') != -1){
		return false;
	}
	return true;
}