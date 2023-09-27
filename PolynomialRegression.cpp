#include "PolynomialRegression.h"

PolynomialRegression::PolynomialRegression()
{
}

double PolynomialRegression::polynomialDegree0(double x, double w0)
{
	return w0;
}

double PolynomialRegression::polynomialDegree1(double x, double w0, double w1)
{
	return w0 + (w1 * x);
}

double PolynomialRegression::polynomialDegree2(double x, double w0, double w1, double w2)
{
	return w0 + (w1 * x) + (w2 * pow(x, 2));
}

double PolynomialRegression::polynomialDegree3(double x, double w0, double w1, double w2, double w3)
{
	return w0 + (w1 * x) + (w2 * pow(x, 2)) + (w3 * pow(x, 3));
}

double PolynomialRegression::polynomialDegree4(double x, double w0, double w1, double w2, double w3, double w4)
{
	return w0 + (w1 * x) + (w2 * pow(x, 2)) + (w3 * pow(x, 3)) + (w4 * pow(x, 4));
}

double PolynomialRegression::polynomialDegree5(double x, double w0, double w1, double w2, double w3, double w4, double w5)
{
	return w0 + (w1 * x) + (w2 * pow(x, 2)) + (w3 * pow(x, 3)) + (w4 * pow(x, 4)) + (w5 * pow(x, 5));
}

double PolynomialRegression::polynomialDegree6(double x, double w0, double w1, double w2, double w3, double w4, double w5, double w6)
{
	return w0 + (w1 * x) + (w2 * pow(x, 2)) + (w3 * pow(x, 3)) + (w4 * pow(x, 4)) + (w5 * pow(x, 5)) + (w6 * pow(x, 6));
}

void PolynomialRegression::setTarget(std::vector<std::pair<double, double>> target)
{
	this->target = target;
}

double PolynomialRegression::mse(std::vector<std::pair<double, double>> prediction, std::vector<std::pair<double, double>> target)
{
	int m = target.size();
	double sum = 0;
	for (int i = 0; i < m; i++)
		sum += ((prediction[i].second - target[i].second) * (prediction[i].second - target[i].second));

	return (sum / (2 * m));
}

std::tuple<std::vector<double>, double, double, double, double> PolynomialRegression::gradientDescent(int degree)
{
	// Z-score normalization
	//----------------------------------------------------------------------------------------------------------------------------------------
	std::vector<double> x_values;
	std::vector<double> y_values;

	for (auto const& p : target) {
		x_values.push_back(p.first);
		y_values.push_back(p.second);
	}

	double x_mean = std::accumulate(x_values.begin(), x_values.end(), 0.0) / x_values.size();
	double x_std = std::sqrt(std::inner_product(x_values.begin(), x_values.end(), x_values.begin(), 0.0) / x_values.size() - x_mean * x_mean);
	double y_mean = std::accumulate(y_values.begin(), y_values.end(), 0.0) / y_values.size();;
	double y_std = std::sqrt(std::inner_product(y_values.begin(), y_values.end(), y_values.begin(), 0.0) / y_values.size() - y_mean * y_mean);

	for (auto & p : target)
		p = { (p.first - x_mean) / x_std, (p.second - y_mean) / y_std };
	//----------------------------------------------------------------------------------------------------------------------------------------

	if (degree == 0) 
		return { gradientDescentDegree0(), x_mean, x_std, y_mean, y_std };
	else if (degree == 1) 
		return { gradientDescentDegree1(), x_mean, x_std, y_mean, y_std };
	else if (degree == 2) 
		return { gradientDescentDegree2(), x_mean, x_std, y_mean, y_std };
	else if (degree == 3) 
		return { gradientDescentDegree3(), x_mean, x_std, y_mean, y_std };
	else if (degree == 4) 
		return { gradientDescentDegree4(), x_mean, x_std, y_mean, y_std };
	else if (degree == 5) 
		return { gradientDescentDegree5(), x_mean, x_std, y_mean, y_std };
	else if (degree == 6) 
		return { gradientDescentDegree6(), x_mean, x_std, y_mean, y_std };
	else 
		return { std::vector<double>(), 0, 0, 0, 0};

}

double PolynomialRegression::dMSE_dw(std::vector<std::pair<double, double>> prediction, std::vector<std::pair<double, double>> target, int w)
{

	if (w == 0) {

		int m = target.size();
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += ((prediction[i].second - target[i].second)*(1));

		return (sum / m);

	}
	else if (w == 1) {

		int m = target.size();
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += ((prediction[i].second - target[i].second) * target[i].first);

		return (sum / m);

	}
	else if (w == 2) {

		int m = target.size();
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += ((prediction[i].second - target[i].second) * pow(target[i].first,2));

		return (sum / m);

	}
	else if (w == 3) {

		int m = target.size();
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += ((prediction[i].second - target[i].second) * pow(target[i].first, 3));

		return (sum / m);

	}
	else if (w == 4) {

		int m = target.size();
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += ((prediction[i].second - target[i].second) * pow(target[i].first, 4));

		return (sum / m);

	}
	else if (w == 5) {

		int m = target.size();
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += ((prediction[i].second - target[i].second) * pow(target[i].first, 5));

		return (sum / m);

	}
	else if (w == 6) {

		int m = target.size();
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += ((prediction[i].second - target[i].second) * pow(target[i].first, 6));

		return (sum / m);

	}
	else {
		return 0;
	}

}

std::vector<double> PolynomialRegression::gradientDescentDegree0()
{
	double w0 = 0;
	double alpha = 0.01;

	double max_iter = 500000;
	double tol = 0.000001;
	double prev_mse = INT_MAX;
	int iter = 0;
	int m = target.size();

	while (true) {

		std::vector<std::pair<double, double>> prediction;
		for (auto const& p : target) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree0(x_prediction, w0);

			prediction.push_back({ x_prediction, y_prediction });

		}

		double curr_mse = mse(prediction, target);

		if ((abs(curr_mse - prev_mse) < tol) || iter == max_iter)
			break;

		double dJ_dw0 = dMSE_dw(prediction, target, 0);

		w0 = w0 - alpha * dJ_dw0;

		prev_mse = curr_mse;
		iter++;

	}

	std::vector<double> coefficient;
	coefficient.push_back(w0);

	return coefficient;
}

std::vector<double> PolynomialRegression::gradientDescentDegree1()
{
	double w0 = 0;
	double w1 = 0;
	double alpha = 0.01;

	double max_iter = 500000;
	double tol = 0.000001;
	double prev_mse = INT_MAX;
	int iter = 0;
	int m = target.size();

	while (true) {

		std::vector<std::pair<double, double>> prediction;
		for (auto const& p : target) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree1(x_prediction, w0, w1);

			prediction.push_back({ x_prediction, y_prediction });

		}

		double curr_mse = mse(prediction, target);

		if ((abs(curr_mse - prev_mse) < tol) || iter == max_iter)
			break;

		double dJ_dw0 = dMSE_dw(prediction, target, 0);
		double dJ_dw1 = dMSE_dw(prediction, target, 1);

		w0 = w0 - alpha * dJ_dw0;
		w1 = w1 - alpha * dJ_dw1;

		prev_mse = curr_mse;
		iter++;

	}

	std::vector<double> coefficient;
	coefficient.push_back(w0);
	coefficient.push_back(w1);

	return coefficient;
}

std::vector<double> PolynomialRegression::gradientDescentDegree2()
{
	double w0 = 0;
	double w1 = 0;
	double w2 = 0;
	double alpha = 0.01;

	double max_iter = 500000;
	double tol = 0.000001;
	double prev_mse = INT_MAX;
	int iter = 0;
	int m = target.size();

	while (true) {

		std::vector<std::pair<double, double>> prediction;
		for (auto const& p : target) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree2(x_prediction, w0, w1, w2);

			prediction.push_back({ x_prediction, y_prediction });

		}

		double curr_mse = mse(prediction, target);

		if ((abs(curr_mse - prev_mse) < tol) || iter == max_iter)
			break;

		double dJ_dw0 = dMSE_dw(prediction, target, 0);
		double dJ_dw1 = dMSE_dw(prediction, target, 1);
		double dJ_dw2 = dMSE_dw(prediction, target, 2);

		w0 = w0 - alpha * dJ_dw0;
		w1 = w1 - alpha * dJ_dw1;
		w2 = w2 - alpha * dJ_dw2;

		prev_mse = curr_mse;
		iter++;

	}
	std::vector<double> coefficient;
	coefficient.push_back(w0);
	coefficient.push_back(w1);
	coefficient.push_back(w2);

	return coefficient;
}

std::vector<double> PolynomialRegression::gradientDescentDegree3()
{
	// Weights
	double w0 = 0;
	double w1 = 0;
	double w2 = 0;
	double w3 = 0;

	// Optimal Weights
	double b0 = 0;
	double b1 = 0;
	double b2 = 0;
	double b3 = 0;

	double alpha = 0.01; // Learning Rate
	int epochs = 500000;

	int m = static_cast<int>(ceil(target.size()) / 10); // Mini-Batch size
	std::random_device rd;
	std::mt19937 g(rd());

	double minError = INT_MAX;

	// Minibatch (stochastic) gradient descent
	for (int i = 0; i < epochs; i++) {

		std::shuffle(target.begin(), target.end(), g);
		std::vector<std::pair<double, double>> miniBatch;

		size_t nelems = m;
		std::sample(
			target.begin(),
			target.end(),
			std::back_inserter(miniBatch),
			nelems,
			std::mt19937{ std::random_device{}() }
		);

		std::vector<std::pair<double, double>> prediction;
		for (auto const& p : miniBatch) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree3(x_prediction, w0, w1, w2, w3);

			prediction.push_back({ x_prediction, y_prediction });

		}

		double currentMSE = mse(prediction, miniBatch);

		double dJ_dw0 = dMSE_dw(prediction, miniBatch, 0);
		double dJ_dw1 = dMSE_dw(prediction, miniBatch, 1);
		double dJ_dw2 = dMSE_dw(prediction, miniBatch, 2);
		double dJ_dw3 = dMSE_dw(prediction, miniBatch, 3);

		w0 = w0 - alpha * dJ_dw0;
		w1 = w1 - alpha * dJ_dw1;
		w2 = w2 - alpha * dJ_dw2;
		w3 = w3 - alpha * dJ_dw3;

		// Save the best weights
		// ----------------------------------------------------------------------------------------------
		std::vector<std::pair<double, double>> guess;
		for (auto const& p : target) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree3(x_prediction, w0, w1, w2, w3);

			guess.push_back({ x_prediction, y_prediction });

		}

		double error = mse(guess, target);
		if (error < minError) {

			minError = error;

			b0 = w0;
			b1 = w1;
			b2 = w2;
			b3 = w3;

		}
		// ----------------------------------------------------------------------------------------------

	}

	std::vector<double> coefficient;
	coefficient.push_back(b0);
	coefficient.push_back(b1);
	coefficient.push_back(b2);
	coefficient.push_back(b3);

	return coefficient;
}

std::vector<double> PolynomialRegression::gradientDescentDegree4()
{
	// Weights
	double w0 = 0;
	double w1 = 0;
	double w2 = 0;
	double w3 = 0;
	double w4 = 0;

	// Optimal Weights
	double b0 = 0;
	double b1 = 0;
	double b2 = 0;
	double b3 = 0;
	double b4 = 0;

	double alpha = 0.01; // Learning Rate
	int epochs = 500000;

	int m = static_cast<int>(ceil(target.size() / 10)); // Mini-Batch size
	std::random_device rd;
	std::mt19937 g(rd());

	double minError = INT_MAX;

	// Minibatch (stochastic) gradient descent
	for (int i = 0; i < epochs; i++) {

		std::shuffle(target.begin(), target.end(), g);
		std::vector<std::pair<double, double>> miniBatch;

		size_t nelems = m;
		std::sample(
			target.begin(),
			target.end(),
			std::back_inserter(miniBatch),
			nelems,
			std::mt19937{ std::random_device{}() }
		);

		std::vector<std::pair<double, double>> prediction;
		for (auto const& p : miniBatch) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree4(x_prediction, w0, w1, w2, w3, w4);

			prediction.push_back({ x_prediction, y_prediction });

		}

		double currentMSE = mse(prediction, miniBatch);

		double dJ_dw0 = dMSE_dw(prediction, miniBatch, 0);
		double dJ_dw1 = dMSE_dw(prediction, miniBatch, 1);
		double dJ_dw2 = dMSE_dw(prediction, miniBatch, 2);
		double dJ_dw3 = dMSE_dw(prediction, miniBatch, 3);
		double dJ_dw4 = dMSE_dw(prediction, miniBatch, 4);

		w0 = w0 - alpha * dJ_dw0;
		w1 = w1 - alpha * dJ_dw1;
		w2 = w2 - alpha * dJ_dw2;
		w3 = w3 - alpha * dJ_dw3;
		w4 = w4 - alpha * dJ_dw4;

		// Save the best weights
		// ----------------------------------------------------------------------------------------------
		std::vector<std::pair<double, double>> guess;
		for (auto const& p : target) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree4(x_prediction, w0, w1, w2, w3, w4);

			guess.push_back({ x_prediction, y_prediction });

		}

		double error = mse(guess, target);
		if (error < minError) {

			minError = error;

			b0 = w0;
			b1 = w1;
			b2 = w2;
			b3 = w3;
			b4 = w4;

		}
		// ----------------------------------------------------------------------------------------------

	}

	std::vector<double> coefficient;
	coefficient.push_back(b0);
	coefficient.push_back(b1);
	coefficient.push_back(b2);
	coefficient.push_back(b3);
	coefficient.push_back(b4);

	return coefficient;
}

std::vector<double> PolynomialRegression::gradientDescentDegree5()
{
	// Weights
	double w0 = 0;
	double w1 = 0;
	double w2 = 0;
	double w3 = 0;
	double w4 = 0;
	double w5 = 0;

	// Optimal Weights
	double b0 = 0;
	double b1 = 0;
	double b2 = 0;
	double b3 = 0;
	double b4 = 0;
	double b5 = 0;

	double alpha = 0.001; // Learning Rate
	int epochs = 1000000;

	int m = static_cast<int>(ceil(target.size() / 20)); // Mini-Batch size
	std::random_device rd;
	std::mt19937 g(rd());

	double minError = INT_MAX;

	// Minibatch (stochastic) gradient descent
	for (int i = 0; i < epochs; i++) {

		std::shuffle(target.begin(), target.end(), g);
		std::vector<std::pair<double, double>> miniBatch;

		size_t nelems = m;
		std::sample(
			target.begin(),
			target.end(),
			std::back_inserter(miniBatch),
			nelems,
			std::mt19937{ std::random_device{}() }
		);

		std::vector<std::pair<double, double>> prediction;
		for (auto const& p : miniBatch) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree5(x_prediction, w0, w1, w2, w3, w4, w5);

			prediction.push_back({ x_prediction, y_prediction });

		}

		double currentMSE = mse(prediction, miniBatch);

		double dJ_dw0 = dMSE_dw(prediction, miniBatch, 0);
		double dJ_dw1 = dMSE_dw(prediction, miniBatch, 1);
		double dJ_dw2 = dMSE_dw(prediction, miniBatch, 2);
		double dJ_dw3 = dMSE_dw(prediction, miniBatch, 3);
		double dJ_dw4 = dMSE_dw(prediction, miniBatch, 4);
		double dJ_dw5 = dMSE_dw(prediction, miniBatch, 5);

		w0 = w0 - alpha * dJ_dw0;
		w1 = w1 - alpha * dJ_dw1;
		w2 = w2 - alpha * dJ_dw2;
		w3 = w3 - alpha * dJ_dw3;
		w4 = w4 - alpha * dJ_dw4;
		w5 = w5 - alpha * dJ_dw5;

		// Save the best weights
		// ----------------------------------------------------------------------------------------------
		std::vector<std::pair<double, double>> guess;
		for (auto const& p : target) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree5(x_prediction, w0, w1, w2, w3, w4, w5);

			guess.push_back({ x_prediction, y_prediction });

		}

		double error = mse(guess, target);
		if (error < minError) {

			minError = error;

			b0 = w0;
			b1 = w1;
			b2 = w2;
			b3 = w3;
			b4 = w4;
			b5 = w5;

		}
		// ----------------------------------------------------------------------------------------------

	}

	std::vector<double> coefficient;
	coefficient.push_back(b0);
	coefficient.push_back(b1);
	coefficient.push_back(b2);
	coefficient.push_back(b3);
	coefficient.push_back(b4);
	coefficient.push_back(b5);

	return coefficient;
}

std::vector<double> PolynomialRegression::gradientDescentDegree6()
{
	// Weights
	double w0 = 0;
	double w1 = 0;
	double w2 = 0;
	double w3 = 0;
	double w4 = 0;
	double w5 = 0;
	double w6 = 0;

	// Optimal Weights
	double b0 = 0;
	double b1 = 0;
	double b2 = 0;
	double b3 = 0;
	double b4 = 0;
	double b5 = 0;
	double b6 = 0;

	double alpha = 0.001; // Learning Rate
	int epochs = 1000000;

	int m = static_cast<int>(ceil(target.size() / 20)); // Mini-Batch size
	std::random_device rd;
	std::mt19937 g(rd());

	double minError = INT_MAX;

	// Minibatch (stochastic) gradient descent
	for (int i = 0; i < epochs; i++) {

		std::shuffle(target.begin(), target.end(), g);
		std::vector<std::pair<double, double>> miniBatch;

		size_t nelems = m;
		std::sample(
			target.begin(),
			target.end(),
			std::back_inserter(miniBatch),
			nelems,
			std::mt19937{ std::random_device{}() }
		);

		std::vector<std::pair<double, double>> prediction;
		for (auto const& p : miniBatch) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree6(x_prediction, w0, w1, w2, w3, w4, w5, w6);

			prediction.push_back({ x_prediction, y_prediction });

		}

		double currentMSE = mse(prediction, miniBatch);

		double dJ_dw0 = dMSE_dw(prediction, miniBatch, 0);
		double dJ_dw1 = dMSE_dw(prediction, miniBatch, 1);
		double dJ_dw2 = dMSE_dw(prediction, miniBatch, 2);
		double dJ_dw3 = dMSE_dw(prediction, miniBatch, 3);
		double dJ_dw4 = dMSE_dw(prediction, miniBatch, 4);
		double dJ_dw5 = dMSE_dw(prediction, miniBatch, 5);
		double dJ_dw6 = dMSE_dw(prediction, miniBatch, 6);

		w0 = w0 - alpha * dJ_dw0;
		w1 = w1 - alpha * dJ_dw1;
		w2 = w2 - alpha * dJ_dw2;
		w3 = w3 - alpha * dJ_dw3;
		w4 = w4 - alpha * dJ_dw4;
		w5 = w5 - alpha * dJ_dw5;
		w6 = w6 - alpha * dJ_dw6;

		// Save the best weights
		// ----------------------------------------------------------------------------------------------
		std::vector<std::pair<double, double>> guess;
		for (auto const& p : target) {

			double x_target = p.first;
			double y_target = p.second;

			double x_prediction = x_target;
			double y_prediction = polynomialDegree6(x_prediction, w0, w1, w2, w3, w4, w5, w6);

			guess.push_back({ x_prediction, y_prediction });

		}

		double error = mse(guess, target);
		if (error < minError) {

			minError = error;

			b0 = w0;
			b1 = w1;
			b2 = w2;
			b3 = w3;
			b4 = w4;
			b5 = w5;
			b6 = w6;

		}
		// ----------------------------------------------------------------------------------------------

	}

	std::vector<double> coefficient;
	coefficient.push_back(b0);
	coefficient.push_back(b1);
	coefficient.push_back(b2);
	coefficient.push_back(b3);
	coefficient.push_back(b4);
	coefficient.push_back(b5);
	coefficient.push_back(b6);

	return coefficient;
}