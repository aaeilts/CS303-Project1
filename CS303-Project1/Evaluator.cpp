#include <cmath>
#include <iostream>
#include "Evaluator.h"
using namespace std;

Evaluator::Evaluator() {
}

Evaluator::Evaluator(string exp) {
	string expression = exp;
	//char precedence[] = { '!', 'i', 'd', '-', '^', '*', '/', '%', '+', '>', 'g', '<', 'l', 'e', 'n', 'a', 'o' };
}

stack <int> Evaluator::GetOperands() {
	return this->operands;
}

stack <char> Evaluator::GetOperators() {
	return this->operators;
}

//checks if char is in list of operators
int Evaluator::isOperator(char symbol) {

	switch (symbol) {
	case '!':
	case 'i':
	case 'd':
	case '-':
	case '^':
	case '*':
	case '/':
	case '%':
	case '+':
	case '>':
	case '<':
	case 'g':
	case 'l':
	case 'e':
	case 'n':
	case 'a':
	case 'o':
	case ')':
	case '(':
		return 1;
		break;
	default:
		return 0;
	}
}

//gets precedence of operator
int Evaluator::GetPrecedence(char compOp) {
	// Use switch case, and strings
	switch (compOp) {
	case '!':
	case 'i':
	case 'd':
	case '-':
		return 8;
		break;
	case '^':
		return 7;
		break;
	case '*':
	case '/':
	case '%':
		return 6;
		break;
	case '+': //negative would also go here? start expression with 0 to make use neg
		return 5;
		break;
	case '>':
	case 'g':
	case '<':
	case 'l':
		return 4;
		break;
	case 'e':
	case 'n':
		return 3;
		break;
	case 'a':
		return 2;
		break;
	case 'o':
		return 1;
		break;
	default:
		return -1;
	}
}

//removes, whitespace, looks for errors, changes double char operators to short hand
void Evaluator::CleanExpression(string expression) {
	//Check for # space # error
	//FIX ME FIX CHAR IF NOT IN ARRAY TO SAY ERROR
	expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());
	for (int i = 0; i < expression.size() - 1; i++) {
		if (expression.at(i) == expression.at(i + 1)) {
			if (expression.at(i) == '+') {
				expression.replace(i, 2, "i");
			}
			else if (expression.at(i) == '-') {
				expression.replace(i, 2, "d");
			}
			else if (expression.at(i) == '=') {
				expression.replace(i, 2, "e");
			}
			else if (expression.at(i) == '&') {
				expression.replace(i, 2, "a");
			}
			else if (expression.at(i) == '|') {
				expression.replace(i, 2, "o");
			}
		}
		else if (expression.at(i + 1) == '=') {
			if (expression.at(i) == '>') {
				expression.replace(i, 2, "g");
			}
			if (expression.at(i) == '<') {
				expression.replace(i, 2, "l");
			}
			if (expression.at(i) == '!') {
				expression.replace(i, 2, "n");
			}
		}
	}
	//FIX ME EXIT PROGRAM WITH ERROR
	try {
		if (expression.at(0) == ')') {
			cout << "Expression cannot start with a closing parenthesis @ char: 0" << endl;
		}
		else if ((expression.at(0) == '>') || (expression.at(0) == '<') || (expression.at(0) == 'g') || (expression.at(0) == 'l') || (expression.at(0) == 'e') || (expression.at(0) == 'n') || (expression.at(0) == 'a') || (expression.at(0) == 'o')) {
			cout << "Expression cannot start with a binary operator @ char: 0" << endl;
		}
		for (int i = 0; i < expression.size() - 1; i++) {
			if (expression.at(i) == expression.at(i + 1)) {
				if ((expression.at(i) == '>') || (expression.at(i) == '<') || (expression.at(i) == 'g') || (expression.at(i) == 'l') || (expression.at(i) == 'e') || (expression.at(i) == 'n') || (expression.at(i) == 'a') || (expression.at(i) == 'o')) {
					cout << "Two binary operators in a row @ char: " << i + 1 << endl;
				}
			}
			if ((expression.at(i) == '/') && (expression.at(i + 1) == '0')) {
				cout << "Division by zero @ char: " << i + 1 << endl;
			}
		}
	}
	catch(){

	}
	
	cout << "TEST: " << expression; //TEST 
}

//converts infix expression to postfix expression
void Evaluator::converter(string expression) {
	string post = "";
	char symbol;
	for (int i = 0; i < expression.length(); i++) {
		if (isdigit(expression.at(i))) {
			post.append(expression.at(i));
		}
		else if (expression.at(i) == '(') {
			this->operators.push(expression.at(i));
		}
		else if (expression.at(i) == ')') {
			while ((expression.length() != 0) && (operators.top() != '(')) {
				symbol = operators.top();
				operators.pop();
				post.append(symbol);
			}
		}
		else if (isOperator(expression.at(i) == 1)) {
			if ((operators.empty() == True) || (operators.top() == '(')) {
				this->operators.push(expression.at(i));
			}
			else {
				while ((expression.length() != 0) && (operators.top() != '(') && (GetPrecedence(expression.at(i)) <= (GetPrecedence(operators.top())))) {
					symbol = operators.top();
					operators.pop();
					post.append(symbol);
				}
			}
		}
	}
	while (expression.length() != 0) {
		symbol = operators.top();
		operators.pop();
		post.append(symbol);
	}
	expression = post;
}

//evaluates the postfix expression
int Evaluator::EvalExpression(string expression) {
	int a, b, c, result;
	for (int i = 0; i < expression.length(); i++) {
		if (isdigit(expression.at(i))) {
			this->operands.push(expression.at(i));
		}
		else if (isOperator(expression.at(i))) {
			a = operands.top();
			operands.pop();
			b = operands.top();
			operands.pop();
			c = TheMath(a, b, expression.at(i));
			this->operands.push(c);
		}
	}
	result = operands.top();
}

//evaluates the mathmatical value of the two numbers and the operator
int Evaluator::TheMath(int left, int right, char opert) {
	switch (opert) {
	case '!':
		if (left == right) {
			return 0;
		}
		else {
			return 1;
		}
	case 'i': 
		return right + 1;
	case 'd':
		return right - 1;
	case '-': 
		return left - right;
	case '^':
		return pow(left, right);
	case '*': 
		return left * right;
	case '/': 
		return left / right;
	case '%': 
		return left % right;
	case '+': 
		return left + right;
	case '>':
		if (left > right) {
			return 0;
		}
		else {
			return 1;
		}
	case 'g': 
		if (left >= right) {
			return 0;
		}
		else {
			return 1;
		}
	case '<': 
		if (left < right) {
			return 0;
		}
		else {
			return 1;
		}
	case 'l': 
		if (left <= right) {
			return 0;
		}
		else {
			return 1;
		}
	case 'e': 
		if (left == right) {
			return 0;
		}
		else {
			return 1;
		}
	case 'n': 
		if (left != right) {
			return 0;
		}
		else {
			return 1;
		}
	case 'a': 
		if (left && right) {
			return 0;
		}
		else {
			return 1;
		}
	case 'o':
		if (left || right) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

//runs the expression through the proper functions
int Evaluator::Calculate(string expression) {
	this->CleanExpression(expression);
	this->converter(expression);
	return this->EvalExpression(expression);
};





//would no longer need
int Evaluator::StackEmUp(string expression) {
	int left, right;
	char symbol;
	while (expression.length() != 0) {
		for (int i = 0; i < expression.length(); i++) {
			//if a number
			if (isdigit(expression.at(i))) {
				this->operands.push(expression.at(i));
			}
			//if a operator symbol
			else if (isOperator(expression.at(i)) == 1) {

			}
			if (expression.at(i) == '(') {
				this->operators.push(expression.at(i));
			}
			else if (expression.at(i) == ')') {
				this->operators.push(expression.at(i));
			}
			while (operators.top() != '(') {
				symbol = operators.top();
				operators.pop();
				right = operands.top();
				operands.pop();
				left = operands.top();
				operands.pop();
				operands.push(TheMath(left, right, symbol));
			}
			//operators.pop();

			while (!operators.empty()) {
				char thisOp = operators.top();
				while (GetPrecedence(thisOp) <= GetPrecedence(operators.top())) {
					symbol = operators.top();
					operators.pop();
					left = operands.top();
					operands.pop();
					right = operands.top();
					operands.pop();
					operands.push(TheMath(left, right, symbol));
					operators.push(thisOp);
				}
				//GetPrecedence(char) returns int value precedence
			}
		}
	}
	while (!operators.empty()) {
		symbol = operators.top();
		operators.pop();
		left = operands.top();
		operands.pop();
		right = operands.top();
		operands.pop();
		operands.push(TheMath(left, right, symbol));
	}
	int result = operands.top();
	return result;
}
