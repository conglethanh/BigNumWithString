#include "OperatorBigNumber.h"

int countNumAfterDot(string a){
	int dem = 0;
	for (int i = a.length() - 1; i > a.find('.'); i--){
		dem++;
	}
	return dem;
}

void fixed(string &a, string &b){
	int ca = countNumAfterDot(a);
	int cb = countNumAfterDot(b);
	if (ca < cb)
	{
		for (int i = 0; i < cb - ca; i++)
			a += '0';
	}
	else
	{
		for (int i = 0; i < ca - cb; i++)
			b += '0';
	}
}

void fixed(string& a, string src, string dest){
	int pos = a.find(src);
	if (pos != -1)
		a.replace(pos, 1, dest);
}

bool isNegative(string a){
	if (a[0] == '-')
		return true;
	return false;
}

string add(string a, string b)
{
	string res = "";
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	int carry = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int tmp = a[i] - 48 + b[i] - 48 + carry;
		carry = tmp / 10;
		tmp = tmp % 10;
		res = (char)(tmp + 48) + res;
	}
	if (carry>0) res = "1" + res;
	return res;
}

string sub(string a, string b)
{
	string res = "";
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	bool neg = false;
	if (a < b)
	{
		swap(a, b);
		neg = true;
	}
	int borrow = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int tmp = a[i] - b[i] - borrow;
		if (tmp<0)
		{
			tmp += 10;
			borrow = 1;
		}
		else borrow = 0;
		res = (char)(tmp % 10 + 48) + res;
	}
	while (res.length()>1 && res[0] == '0') res.erase(0, 1);
	if (neg) res = "-" + res;
	return res;
}

string mul(string a, string b)
{
	string res = "";
	int n = a.length();
	int m = b.length();
	int len = n + m - 1;
	int carry = 0;
	for (int i = len; i >= 0; i--)
	{
		int tmp = 0;
		for (int j = n - 1; j >= 0; j--)
		if (i - j <= m && i - j >= 1)
		{
			int a1 = a[j] - 48;
			int b1 = b[i - j - 1] - 48;
			tmp += a1*b1;
		}
		tmp += carry;
		carry = tmp / 10;
		res = (char)(tmp % 10 + 48) + res;
	}
	while (res.length() > 1 && res[0] == '0') res.erase(0, 1);
	return res;
}

string longDivision(string number, long long  divisor)
{
	string ans;

	int idx = 0;
	long long temp = number[idx] - '0';
	while (temp < divisor)
		temp = temp * 10 + (number[++idx] - '0');

	while (number.size() > idx)
	{
		ans += (temp / divisor) + '0';
		temp = (temp % divisor) * 10 + number[++idx] - '0';
	}

	if (ans.length() == 0)
		return "0";

	return ans;
}

string powerBig(string number, int power){
	string res = "1";
	for (int i = 0; i < power; i++){
		res = mul(res, number);
	}
	return res;
}

string addBigReal(string a, string b){
	if (a.find('.') == -1 && b.find('.') == -1)
		return add(a, b);
	string res = "";
	int countA = countNumAfterDot(a);
	int countB = countNumAfterDot(b);
	int count = (countA > countB) ? countA : countB;
	fixed(a, b);
	fixed(a, ".", "");
	fixed(b, ".", "");
	res = add(a, b);
	res.insert(res.length() - count, ".");
	return res;
}

string subBigReal(string a, string b){
	if (a.find('.') == -1 && b.find('.') == -1)
		return sub(a, b);
	string res = "";
	int countA = countNumAfterDot(a);
	int countB = countNumAfterDot(b);
	int count = (countA > countB) ? countA : countB;
	fixed(a, b);
	fixed(a, ".", "");
	fixed(b, ".", "");
	res = sub(a, b);

	int tmp = res.length();

	if (count >= tmp){
		res = "0" + res;
		for (int i = 0; i < count - tmp; i++){
			res = "0" + res;
		}
		res.insert(res.length() - count, ".");
		while (res[res.length() - 1] == '0'){
			res.erase(res.length() - 1, 1);
		}
		int q = res.find("-");
		if (q != -1) {
			res.erase(q, 1);
			res = "0" + res;
			res = "-" + res;
			int k = res.find(".");
			if (k != 2)
			{
				res.erase(k, 1);
				res.insert(2, ".");
			}
		}
	}
	else
	{
		res.insert(res.length() - count, ".");
		if (res[0] == '-'&&res[1] == '.')
			res.insert(1, "0");
	}
	return res;
}

string mulBigReal(string a, string b){
	if (a.find('.') == -1 && b.find('.') == -1)
		return mul(a, b);
	string res = "";
	int countA = countNumAfterDot(a);
	int countB = countNumAfterDot(b);
	int count = countA + countB;
	fixed(a, ".", "");
	fixed(b, ".", "");
	res = mul(a, b);
	int tmp = res.length();

	if (count > tmp){
		res = "0" + res;
		for (int i = 0; i < count - tmp; i++){
			res = "0" + res;
		}
	}
	res.insert(res.length() - count, ".");
	while (res[res.length() - 1] == '0'){
		res.erase(res.length() - 1, 1);
	}
	return res;
}

string addFinal(string a, string b){
	if (isNegative(a) == true && isNegative(b) == false){
		fixed(a, "-", "");
		return subBigReal(b, a);
	}
	if (isNegative(a) == false && isNegative(b) == true){
		fixed(b, "-", "");
		return subBigReal(a, b);
	}
	if (isNegative(a) == true && isNegative(b) == true){
		string res;
		fixed(a, "-", "");
		fixed(b, "-", "");
		res = addBigReal(a, b);
		res = "-" + res;
		return res;
	}
	return addBigReal(a, b);
}

string subFinal(string a, string b){
	if (isNegative(a) == true && isNegative(b) == false){
		string res;
		fixed(a, "-", "");
		res = addBigReal(a, b);
		res = "-" + res;
		return res;
	}
	if (isNegative(a) == false && isNegative(b) == true){
		fixed(b, "-", "");
		return addBigReal(a, b);
	}
	if (isNegative(a) == true && isNegative(b) == true){
		fixed(a, "-", "");
		fixed(b, "-", "");
		return subBigReal(b, a);
	}
	return subBigReal(a, b);
}

string mulFinal(string a, string b){
	if (isNegative(a) == true && isNegative(b) == false){
		fixed(a, "-", "");
		string res;
		res = mulBigReal(a, b);
		res = "-" + res;
		return res;
	}
	if (isNegative(a) == false && isNegative(b) == true){
		fixed(b, "-", "");
		string res;
		res = mulBigReal(a, b);
		res = "-" + res;
		return res;
	}
	if (isNegative(a) == true && isNegative(b) == true){
		string res;
		fixed(a, "-", "");
		fixed(b, "-", "");
		return mulBigReal(a, b);
	}
	return mulBigReal(a, b);
}

string powerFinal(string a, string power){
	string res = "1";
	int p = stoi(power);
	for (int i = 0; i < p; i++){
		res = mulFinal(res, a);
	}
	return res;
}

string divDotDecimal(string number, string divisor){
	int count = 0;
	string res;

	if (stoll(number) < stoll(divisor)){
		res = "0.";
		while (stoll(number) < stoll(divisor)){
			number = number + '0';
			if (stoll(number) < stoll(divisor))
				res = res + '0';
			count++;
		}

		string t = longDivision(number, stoll(divisor));
		res = res + t;
		string mod = subFinal(number, mulFinal(t, divisor));

		while (stoll(mod) < stoll(divisor) && mod != "0"){
			mod = mod + '0';
			if (stoll(mod) < stoll(divisor)){
				res = res + '0';
			}
			count++;
			if (stoll(mod) > stoll(divisor)){
				string k = longDivision(mod, stoll(divisor));
				res = res + k;
				mod = subFinal(mod, mulFinal(k, divisor));
			}
			if (count == ROUND_NUM)
				break;
		}
		return res;
	}
	else
	{
		res = longDivision(number, stoll(divisor));
		string mod = subFinal(number, mulFinal(res, divisor));
		if (mod != "0")
			res = res + ".";
		while (stoll(mod)<stoll(divisor) && mod != "0"){
			mod = mod + '0';
			count++;
			if (stoll(mod) > stoll(divisor)){
				string k = longDivision(mod, stoll(divisor));
				res = res + k;
				mod = subFinal(mod, mulFinal(k, divisor));
			}
			if (count == ROUND_NUM)
				break;
		}
		return res;
	}
}

string divBigReal(string number, string divisor){
	fixed(number, divisor);
	fixed(number, ".", "");
	fixed(divisor, ".", "");
	return divDotDecimal(number, divisor);
}

string divFinal(string a, string b){
	if (isNegative(a) == true && isNegative(b) == false){
		fixed(a, "-", "");
		string res;
		res = divBigReal(a, b);
		res = "-" + res;
		return res;
	}
	if (isNegative(a) == false && isNegative(b) == true){
		fixed(b, "-", "");
		string res;
		res = divBigReal(a, b);
		res = "-" + res;
		return res;
	}
	if (isNegative(a) == true && isNegative(b) == true){
		string res;
		fixed(a, "-", "");
		fixed(b, "-", "");
		return divBigReal(a, b);
	}
	return divBigReal(a, b);
}

string roundBigNum(string &a){
	while (countNumAfterDot(a) > ROUND_NUM){
		a.erase(a.length() - 1, 1);
	}
	return a;
}