#pragma once

#include <unordered_set>
#include <stack>
#include <ctype.h>

class Validity
{
	private:
		std::unordered_set<std::string> valid_string{ "(", ")", "+", "-", "*", "/", "^", "abs", "exp", "ln", "log", "sgn", "sinc", "sin", "cos", "tan", "csc", "sec", "cot", "arctan", "arccos", "arcsin", "sinh", "cosh", "tanh", "factorial", "sqrt", "x", "-1" };
		std::unordered_set<std::string> func{ "abs", "exp", "ln", "log", "sgn", "sinc", "sin", "cos", "tan", "csc", "sec", "cot", "arctan", "arccos", "arcsin", "sinh", "cosh", "tanh", "factorial", "sqrt" };
		std::unordered_set<std::string> oper{ "+", "-", "*", "/", "^" };
	protected:
	public:
		Validity();
		bool validTokens(std::string token);
		bool validParentheses(std::vector<std::string> tokens);
		bool isInfixValid(std::vector<std::string> tokens);
};