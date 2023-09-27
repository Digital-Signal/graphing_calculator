#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <cassert>

class ShuntingYardAlgorithm
{
	private:
		std::unordered_map<std::string, int> operator_precedence{ {"^",4},{"*",3},{"/",3},{"+",2},{"-",2} };
		std::unordered_map<std::string, std::string> operator_associativity{ {"^","Right"},{"*","Left"},{"/","Left"},{"+","Left"},{"-","Left"}};
		std::unordered_set<std::string> func{ "abs", "exp", "ln", "log", "sgn", "sinc", "sin", "cos", "tan", "csc", "sec", "cot", "arctan", "arccos", "arcsin", "sinh", "cosh", "tanh", "factorial", "sqrt" };
		std::unordered_set<std::string> oper{ "+", "-", "*", "/", "^" };
	protected:
	public:
		ShuntingYardAlgorithm();
		std::vector<std::string> infixToPostfix(std::vector<std::string> tokens);
};