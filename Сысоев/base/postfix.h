#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <map>

using namespace std;

class TPostfix
{
	map<string, int> priority;
	map<string, int> ar;
	map<string, int> keyoper;
	string infix;
	string postfix;
public:
	TPostfix()
	{
		priority = { {"+", 1},{"-",1},{"*",2},{"/",2},{"sin",3},{"cos",3},{"log",3},{"^",4} };
		ar = { {"+", 2},{"-",2},{"*",2},{"/",2},{"sin",1},{"cos",1},{"log",1},{"^",2} };
		keyoper = { {"+",1},{"-",2},{"*",3},{"/",4},{"sin",5},{"cos",6},{"log",7},{"^",8} };
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	string ToPostfix();
	void CheckInfix();
	void SetInfix(const string &a) {
		infix = a;
	}
	void SetPostfix(const string &a) { postfix = a; }
	bool Num(const string &str);
	string InsertSpace();
	void DeleteSpaceInfix();
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
