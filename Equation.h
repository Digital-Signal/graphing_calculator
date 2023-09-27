#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <stack>

class Equation
{
	private:
	protected:
	public:
		Equation();
		double function(double x, std::vector<std::string> postfix);
		double factorial(double x);
		int sgn(double x);
		double sinc(double x);
		double cot(double x);
		double sec(double x);
		double csc(double x);

};