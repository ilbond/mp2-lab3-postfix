#include "postfix.h"
#include "stack.h"
#include <sstream>
#include <string>
#include <istream>
#include <vector>
#include <iostream>

void TPostfix::DeleteSpaceInfix() {
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == ' ') {
			infix.erase(i, 1);
		}
	}
}
string TPostfix::InsertSpace() {
	CheckInfix();
	string word;
	string str;
	string res;
	for (int i = 0; i < infix.size(); i++)
	{
		{


			str = infix[i];
			if (((infix[i] >= 40) && (infix[i] <= 47) && (infix[i] != 46) && (infix[i] != 44)) || infix[i] == 94)
			{
				if (word.length() == 0)
				{
					if (i == (infix.length() - 1))
						res += (str);
					else
						res += (str + ' ');
				}
				else
				{
					res += (word + ' ');
					word.clear();
					if (i == (infix.length() - 1))
						res += (str);
					else
						res += (str + ' ');
				}

			}
			else
			{
				word += infix[i];
			}
			if (i == infix.size() - 1)
			{
				res += word;
				word.clear();
			}
		}

	}
	return res;
}
void TPostfix::CheckInfix() {
	DeleteSpaceInfix();
	char Word, PrevWord;
	vector<int> par;
	int i = 0;
	for (stringstream is(infix); is >> Word;) {
		if (((Word < 40) || (Word > 57)) && (((Word < 97) || (Word > 122)) && ((Word < 65) || (Word > 90))) && (Word != 94)) {
			throw 1;
			if (Word == 44)
				throw 1;
		}
		if ((Word >= 48) && (Word <= 57))
			if (i != 0) {
				if (((PrevWord >= 97) && (PrevWord <= 122)) || ((PrevWord >= 65) && (PrevWord <= 90)))
					throw 1;
			}
		if (((Word >= 97) && (Word <= 122)) || ((Word >= 65) && (Word <= 90))) {
			if (i != 0) {
				if (((PrevWord >= 48) && (PrevWord <= 57)) || (PrevWord == '.'))
					throw 1;
			}
		}
		if (((Word >= 42) && (Word <= 47) && (Word != 46)) || (Word == 94)) {
			if (i != 0) {
				if (((PrevWord >= 42) && (PrevWord <= 47) && (PrevWord != 46)) || (PrevWord == 94)) {
					throw 1;
				}
			}
			else throw 1;
		}
		if (Word == '.') {
			if (i == 0) {
				if ((PrevWord < 40) && (PrevWord > 57))
					throw 1;
			}
		}
		if (Word == '(') {
			par.push_back(1);
			if (i != 0) {
				if ((PrevWord >= 48) && (PrevWord <= 57)) {
					throw 1;
				}
			}
		}
		if (Word == ')')
			par.pop_back();

		PrevWord = Word;

		i++;
	}
	if (par.empty() == 0)
		throw 1;
}
string TPostfix::ToPostfix()
{
	string str = InsertSpace();
	CheckInfix();
	TStack <string> stack(MaxStackSize);
	string Word;
	for (stringstream is(str); is >> Word;) {
		if (ar[Word] != 0)
			if (stack.empty()) {
				stack.push(Word);
			}
			else
			{
				while (!stack.empty()) {
					if (priority[stack.gettop()] >= priority[Word]) {

						postfix += ' ';
						postfix += stack.pop();
					}
					else break;
				}

				stack.push(Word);

			}
		if (Word == "(") {
			stack.push(Word);
		}
		if (Word == ")") {
			while (stack.gettop() != "(")
			{
				postfix += ' ';
				postfix += stack.pop();
			}
			stack.pop();
		}
		if ((ar[Word] == 0) && (Word != "(") && (Word != ")")) {
			postfix += ' ';
			postfix += Word;
		}
	}

	while (!stack.empty()) {
		postfix += " ";
		postfix += stack.pop();
	}
	return postfix;
}

double TPostfix::Calculate()
{

	double res;
	map <string, double> val;
	string Word, aux;
	TStack<double> stack(MaxStackSize);
	for (stringstream is(postfix); is >> Word;) {
		if ((ar[Word] == 0) && (!Num(Word))) {
			double a;
			aux = Word;
			cout << aux << "=";
			cin >> a;
			cout << endl;
			val.insert(pair<string, double>(aux, a));
			aux.clear();
		}
	}
	for (stringstream is(postfix); is >> Word;) {
		if (ar[Word] != 0) {
			switch (keyoper[Word])
			{
			case 1: {
				double a = stack.pop();
				double b = stack.pop();
				stack.push(a + b);
				break;
			}
			case 2: {
				double a = stack.pop();
				double b = stack.pop();
				stack.push(b - a);
				break;
			}
			case 3: {
				double a = stack.pop();
				double b = stack.pop();
				stack.push(a * b);
				break;
			}
			case 4: {
				double a = stack.pop();
				double b = stack.pop();
				stack.push(a / b);
				break;
			}
			case 5: {
				double a = stack.pop();
				stack.push(sin(a));
				break;
			}
			case 6: {
				double a = stack.pop();
				stack.push(cos(a));
				break;
			}
			case 7: {
				double a = stack.pop();
				stack.push(log(a));
				break;
			}
			case 8: {
				double a = stack.pop();
				double b = stack.pop();
				stack.push(pow(b, a));
			}
			default:
				break;
			}
		}
		else {
			if (Num(Word)) {
				stringstream tmp(Word);
				double b;
				tmp >> b;
				stack.push(b);
			}
			else {
				stack.push(val[Word]);
			}
		}
	}
	res = stack.pop();
	return res;
}
bool TPostfix::Num(const string &str)
{

	for (int i = 0; i < str.length(); i++)
	{
		if (i == 0)
			if (!((str[i] >= 48) && (str[i] <= 57)))
				return 0;
	}
}