#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <random>
#include <iterator>
#include <string>
#include <tuple>

class PolynomialRegression
{
	private:
		std::vector<std::pair<double, double>> target;
	protected:
	public:
		PolynomialRegression();
		double polynomialDegree0(double x, double w0);
		double polynomialDegree1(double x, double w0, double w1);
		double polynomialDegree2(double x, double w0, double w1, double w2);
		double polynomialDegree3(double x, double w0, double w1, double w2, double w3);
		double polynomialDegree4(double x, double w0, double w1, double w2, double w3, double w4);
		double polynomialDegree5(double x, double w0, double w1, double w2, double w3, double w4, double w5);
		double polynomialDegree6(double x, double w0, double w1, double w2, double w3, double w4, double w5, double w6);
		void setTarget(std::vector<std::pair<double, double>> target);
		double mse(std::vector<std::pair<double, double>> prediction, std::vector<std::pair<double, double>> target);
		std::tuple<std::vector< double>, double, double, double, double> gradientDescent(int degree);
		double dMSE_dw(std::vector<std::pair<double, double>> prediction, std::vector<std::pair<double, double>> target, int w);
		std::vector<double> gradientDescentDegree0();
		std::vector<double> gradientDescentDegree1();
		std::vector<double> gradientDescentDegree2();
		std::vector<double> gradientDescentDegree3();
		std::vector<double> gradientDescentDegree4();
		std::vector<double> gradientDescentDegree5();
		std::vector<double> gradientDescentDegree6();

};