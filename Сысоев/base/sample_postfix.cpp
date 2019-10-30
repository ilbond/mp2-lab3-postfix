#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  TPostfix postfix;
  double res;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  getline(cin, expression);
  postfix.SetInfix(expression);
  cout << expression << endl;
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << res << endl;
  postfix.DeleteSpaceInfix();

  return 0;
}
