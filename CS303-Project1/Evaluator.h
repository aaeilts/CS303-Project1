#include <stack>
#include <string>


using namespace std;

class Evaluator {
public:
	Evaluator();
	Evaluator(string exp);
	stack <int> GetOperands();
	stack <char> GetOperators();
	int isOperator(char symbol);
	int GetPrecedence(char compOp);
	void CleanExpression(string expression);
	int Calculate(string expression);
	void converter(string expression);
	int EvalExpression(string expression);
	int StackEmUp(string expression);
	int TheMath(int left, int right, char opert);
	stack <int> operands;
	stack <char> operators;
	//char  precedence[];

};
