#pragma once

#include <SFML/Graphics.hpp>
#include <tuple>

#include "Equation.h"
#include "PolynomialRegression.h"

class Graph
{
	private:

		// Origin of graph (according to SFML)
		float origin_x;
		float origin_y;

		// Old mouse position -> for dragging/moving the graph
		float old_mouse_x;
		float old_mouse_y;

		float minXCurrent;
		float maxXCurrent;
		float minYCurrent;
		float maxYCurrent;
		float scale_x;
		float scale_y;

		// SFML points (SFML domain)
		sf::VertexArray sfml_points;

		// SFML regression points (SFML domain)
		sf::VertexArray sfml_regression_points;

		// Real points (Real domain)
		std::vector<sf::Vector2f> points;

		sf::Vertex x_axis[2];
		sf::Vertex y_axis[2]; 

		Equation equation;

		std::vector<std::string> postfix; // Reverse Polish notation 

		std::vector<sf::CircleShape> vectorOfPoints;

		double x_mean, x_std, y_mean, y_std;
		std::vector<double> coefficient;

	protected:

	public:
		Graph();
		std::vector<float> linspace(float start, float end, size_t points);
		void zoomInHorizontally();
		void zoomOutHorizonatlly();
		void zoomInVertically();
		void zoomOutVertically();
		void zoomIn();
		void zoomOut();
		void reset();
		void drag(sf::RenderWindow& window);
		void resetMousePosition();
		void draw(sf::RenderWindow& window);
		void setFunction(std::vector<std::string> postfix);
		void update();
		void addPoint(sf::CircleShape c);
		void clearAllPoints();
		void regression(int degree);
		double polynomial(std::vector<double> coef, double x_m, double x_s, double y_m, double y_s, double x);

};