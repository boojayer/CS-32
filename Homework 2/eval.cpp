#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
#include "Map.h"
using namespace std;

int pemdas(char temp);

int evaluate(string infix, const Map& values, string& postfix, int& result)
// Evaluates an integer arithmetic expression
{
	//Initialize postfix to empty
	postfix = "";


	//Initialize the operator stack to empty
	stack<char> operators;

	//For each character ch in the infix string
	//Switch(ch)
	for (int i = 0; i < infix.size(); i++)
	{
		switch (infix[i])
		{
		//case ' ' (spaces)
		case ' ':
			break;


		//case ')':
		case '(':
			if (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' || infix[i + 1] == ')')
				return 1;
			operators.push(infix[i]);
			break;

		//case ')':
		case ')':
			while (operators.top() != '(') 
			{
				postfix += operators.top();
				operators.pop();
			}
			if (operators.empty())
				return 1;
			operators.pop();
			break;

        //case operators
		case '+':
		case '-':
		case '*':
		case '/':
			while (!operators.empty() && operators.top() != '(' && pemdas(infix[i]) <= pemdas(operators.top()))
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.push(infix[i]);
			break;
		default:
			if (isalpha(infix[i]) && islower(infix[i]))
			{
				postfix += infix[i];
				if (infix[i + 1] == '(')
					return 1;
				break;
			}
			else
				return 1;
		}
	}

	while (operators.empty() == false) 
	{
		postfix += operators.top();
		operators.pop();
	}


	double val = 0;
	int operand2 = 0;
	int operand1 = 0;
	//postfix
	stack<int> conclusion;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isalpha(postfix[i]) && islower(postfix[i]))
		{
			if (!values.get(postfix[i], val))
			{
				return 2;
			}
			conclusion.push(val);
		}
		else
		{
			if (conclusion.empty())
				return 1;
			//create first operand
			operand2 = conclusion.top();
			conclusion.pop();
			
			if (conclusion.empty())
				return 1;

			//create second operand
			operand1 = conclusion.top();
			conclusion.pop();
			if (postfix[i] == '+')
			{
				conclusion.push(operand1 + operand2);
			}
			else if(postfix[i] == '-')
			{
				conclusion.push(operand1 - operand2);
			}
			else if (postfix[i] == '*')
			{
				conclusion.push(operand1 * operand2);
			}
			else if (postfix[i] == '/')
			{
				if (operand2 == 0)
					return 3;
				conclusion.push(operand1 / operand2);
			}
		}
	}
	if (conclusion.size() != 1)
		return 1;
	result = conclusion.top();
	return 0;
}
	

int pemdas(char temp)
{
	switch (temp)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return -1;
	}
}


int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int vals[] = { 3, -9, 6, 2, 4, 1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*" && answer == 999);
	assert(evaluate("y +o *( a-u) ", m, pf, answer) == 0 &&
		pf == "yoau-*+" && answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/" && answer == 999);
	assert(evaluate(" a ", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	cout << "Passed all tests" << endl;
}