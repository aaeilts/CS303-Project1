#include <stack>
#include <string>
#include <vector>

using namespace std;

class Evaluator{
public:
	Evaluator();
	stack <int> GetOperand();
	stack <string> GetOperator();
	void CompareOperator();

private:
	stack <int> operands;
	stack <string> operators;
	const vector <int>  precenedence;
};
