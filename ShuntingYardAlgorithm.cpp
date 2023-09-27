#include "ShuntingYardAlgorithm.h"

ShuntingYardAlgorithm::ShuntingYardAlgorithm()
{
}

std::vector<std::string> ShuntingYardAlgorithm::infixToPostfix(std::vector<std::string> tokens)
{
	std::queue<std::string> inputTokenQueue;
	std::queue<std::string> outputTokenQueue;
	std::stack<std::string> operatorStack;

	for (std::string t : tokens) 
		inputTokenQueue.push(t);

	while (!inputTokenQueue.empty()) {

		std::string token = inputTokenQueue.front();
		inputTokenQueue.pop();

		if (token == "-1" || token[0] == '.' || isdigit(token[0]) || token == "x")
			outputTokenQueue.push(token);
		else if (func.count(token))
			operatorStack.push(token);
		else if (oper.count(token)) {
			
			while (!operatorStack.empty() && ((oper.count(operatorStack.top()) && operatorStack.top() != "(") && ((operator_precedence[operatorStack.top()] > operator_precedence[token]) || ((operator_precedence[token] == operator_precedence[operatorStack.top()]) && operator_associativity[token] == "Left")))     ) {

				std::string o2 = operatorStack.top();
				operatorStack.pop();
				outputTokenQueue.push(o2);

			}
			operatorStack.push(token);
		}
		else if (token == "(")
			operatorStack.push(token);
		else if (token == ")") {

			while (!operatorStack.empty() && (oper.count(operatorStack.top()) && operatorStack.top() != "(")) {
				
				assert(!operatorStack.empty());
				std::string o2 = operatorStack.top();
				operatorStack.pop();
				outputTokenQueue.push(o2);

			}
			assert(operatorStack.top() == "(");
			operatorStack.pop();
			if (!operatorStack.empty() && func.count(operatorStack.top())) {

				std::string o2 = operatorStack.top();
				operatorStack.pop();
				outputTokenQueue.push(o2);

			}
		}

	}

	while (!operatorStack.empty()) {
		assert(operatorStack.top() != "(");
		std::string o2 = operatorStack.top();
		operatorStack.pop();
		outputTokenQueue.push(o2);
	}

	std::vector<std::string> output;
	while (!outputTokenQueue.empty()) {
		output.push_back(outputTokenQueue.front());
		outputTokenQueue.pop();
	}

	return output;
}