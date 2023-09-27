#pragma once

#include <string>
#include <vector>
#include <unordered_set>

class Lexer
{
	private:
		std::unordered_set<std::string> func{ "abs", "exp", "ln", "log", "sgn", "sinc", "sin", "cos", "tan", "csc", "sec", "cot", "arctan", "arccos", "arcsin", "sinh", "cosh", "tanh", "factorial", "sqrt" };
	protected:
	public:
		Lexer();
		std::vector<std::string> getTokens(std::string equation);
};