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

//checks if char is in list of operators
int Evaluator::isOperator(char symbol) {
	int i;

	if ((symbol == '!') || (symbol == 'i') || (symbol == 'd') || (symbol == '-') || (symbol == '*') || (symbol == '^') || (symbol == '/') || (symbol == '%') || (symbol == '+') || (symbol == '>') || (symbol == '<') || (symbol == 'g') || (symbol == 'l') || (symbol == 'e') || (symbol == 'n') || (symbol == 'a') || (symbol == 'o')) {
		i = 1;
	}
	else {
		i = 0;
	}
	return i;



	/*switch (symbol) {
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
		i = 1;
		break;
	default:
		i = 0;
	}
	cout << i << endl;
	return i;*/
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
	case '+': 
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
void Evaluator::CleanExpression(string& expression) {
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
	int b = 0;
	try {
		if (expression.at(0) == ')') {
		throw runtime_error("Expression cannot start with a closing parenthesis @ char: 0");
		}
		else if ((expression.at(0) == '>') || (expression.at(0) == '<') || (expression.at(0) == 'g') || (expression.at(0) == 'l') || (expression.at(0) == 'e') || (expression.at(0) == 'n') || (expression.at(0) == 'a') || (expression.at(0) == 'o')) {
			throw runtime_error("Expression cannot start with a binary operator @ char: 0");
		}
		for (int i = 0; i < expression.size() - 1; i++) {
			if (expression.at(i) == expression.at(i + 1)) {
				if ((expression.at(i) == '>') || (expression.at(i) == '<') || (expression.at(i) == 'g') || (expression.at(i) == 'l') || (expression.at(i) == 'e') || (expression.at(i) == 'n') || (expression.at(i) == 'a') || (expression.at(i) == 'o')) {
					b = i;
					throw runtime_error("Two binary operators in a row @ char: FIXME");
				}
			}
			if ((expression.at(i) == '/') && (expression.at(i + 1) == '0')) {
				b = i;
				throw runtime_error("Division by zero @ char: FIXME");
			}
		}
	}
	catch(runtime_error & excpt){
		cout << excpt.what() << endl;
		exit(EXIT_FAILURE);
	} 
}

//converts infix expression to postfix expression
void Evaluator::Converter(string& expression) {
	string post = "";
	char symbol;
	int ops;
	for (int i = 0; i < expression.length(); i++) {
		ops = isOperator(expression.at(i));
		if (isdigit(expression.at(i))) {
			post += expression.at(i);
			//cout << post << endl;
		}
		//this is where we didnt understand the parentheses situation. we got so far but couldnt get them to delete out of the stack.
		/*else if (expression.at(i) == '(') {
			this->operators.push(expression.at(i));
		}
		else if (expression.at(i) == ')') {
			while ((expression.length() != 0) && (operators.top() != '(')) {
				symbol = operators.top();
				operators.pop();
				post += symbol;
			}
		}*/
		else if(ops == 1) {

			if (operators.empty()){
				this->operators.push(expression.at(i));
			}
			else{
				while (!operators.empty()) {
					if (GetPrecedence(expression.at(i)) <= GetPrecedence(operators.top())){
					symbol = operators.top();
					operators.pop();
					post += symbol;
					this->operators.push(expression.at(i));
					break;
					}
					else {
						this->operators.push(expression.at(i));
						break;
					}
				}
			}
		}
	}
	while (!operators.empty()) {
		symbol = operators.top();
		operators.pop();
		post += symbol;
	}
	expression = post;
}

//evaluates the postfix expression
int Evaluator::EvalExpression(string& expression) {
	int a, b, c, result, temp;
	char x;
	for (int i = 0; i < expression.length(); i++) {
		if (isdigit(expression.at(i))) {
			x = expression.at(i);
			temp = x - 48;
			this->operands.push(temp);
		}
		else {
			a = operands.top();
			operands.pop();
			b = operands.top();
			operands.pop();
			c = TheMath(b, a, expression.at(i));
			this->operands.push(c);
		}
	}
	result = operands.top();
	return result;
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
			return 1;
		}
		else {
			return 0;
		}
	case 'g': 
		if (left >= right) {
			return 1;
		}
		else {
			return 0;
		}
	case '<': 
		if (left < right) {
			return 1;
		}
		else {
			return 0;
		}
	case 'l': 
		if (left <= right) {
			return 1;
		}
		else {
			return 0;
		}
	case 'e': 
		if (left == right) {
			return 1;
		}
		else {
			return 0;
		}
	case 'n': 
		if (left != right) {
			return 1;
		}
		else {
			return 0;
		}
	case 'a': 
		if (left && right) {
			return 1;
		}
		else {
			return 0;
		}
	case 'o':
		if (left || right) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

//runs the expression through the proper functions
int Evaluator::Calculate(string expression) {
	this->CleanExpression(expression);
	this->Converter(expression);
	return this->EvalExpression(expression);
};
