#include "QueueLinkedList.h"
#include "StackLinkedList.h"
#include "PreCalc.h"
#include "OperatorBigNumber.h"
#include "PolishNotation.h"
#pragma once

int main(int argc, char* argv[]){
	try
	{
		if (argc != 3){
			//Chế độ mặc định lấy file input.txt xuất ra output.txt
			argv[1] = "input.txt";
			argv[2] = "output.txt";
		}
		//Đọc file
		string s = readFile(argv[1]);
		//Chuẩn hóa xóa khoảng trắng
		standardizeString(s);
		cout << s << endl;
		//Kiểm tra hợp lệ các phép toán, dấu ngoặc
		if (checkValidExpression(s) == false){
			throw ERR_SYNTAX;
		}

		//Chuyển sang dạng tiền tố Ký pháp BaLan
		Queue q = ConvertToPostfix(s);

		//Lưu vào vector<string> để dễ thao tác
		vector<string> baLan;
		while (!isEmpty(q)){
			string k;
			pop(q, k);
			//Kiểm tra toán hạng có hợp lệ về dấu . hay ko?
			if (checkNumberIsValid(k) == false){
				throw ERR_NUMBER;
			}
			baLan.push_back(k);
		}

		//Print the result
		ofstream fo(argv[2]);
		string res = calcBigNumber(baLan);
		cout << "Calculate successfully !" << endl;
		roundBigNum(res);
		while (res[res.length() - 1] == '0')
		{
			res.erase(res.length() - 1, 1);
		}
		cout << "Result: " << res << endl;
		fo << res;
		fo.close();
		system("pause");
		return 0;
	}
	catch (int err)
	{
		if (err == ERR_SYNTAX)
		{
			cout << "Syntax error!... ";
			system("pause");
		}
		if (err == ERR_NUMBER)
		{
			cout << "Syntax error!...Number is invalid!... ";
			system("pause");
		}
		if (err == ERR_INPUT)
		{
			cout << "No file input exists!... ";
			system("pause");
		}
	}
}