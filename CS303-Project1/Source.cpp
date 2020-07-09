#include <string>
#include <iostream>
#include "Evaluator.h"
using namespace std;



int main() {
	Evaluator eval;

	int result = eval.Calculate("1+2*3");
	cout << result << endl;

	return 0;

}

