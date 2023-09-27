#include "Graph.h"

std::vector<float> Graph::linspace(float start, float end, size_t points)
{
    std::vector<float> res(points);
    float step = (end - start) / (points - 1);
    size_t i = 0;
    for (auto& e : res)
        e = start + step * i++;

    return res;
}

void Graph::zoomInHorizontally()
{

    // Update points
    for (sf::CircleShape& p : vectorOfPoints) {
        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        // Modify the scale
        // Convert from real domain to sfml domain
        x = (250 / (scale_x / 1.1f)) * x_real + 250 + (origin_x - 250);
        y = -1 * (250 / (scale_y)) * y_real + 250 + (origin_y - 250);

        // Update the point's position
        p.setPosition(x - 4, y - 4);
    }

    points.clear();

    minXCurrent /= 1.1f;
    maxXCurrent /= 1.1f;

    scale_x /= 1.1f;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    points.clear();

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_regression_points[i].position = points[i];
        sfml_regression_points[i].color = sf::Color::Red;
        sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
        sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
    }

}

void Graph::zoomOutHorizonatlly()
{
    // Update points
    for (sf::CircleShape& p : vectorOfPoints) {
        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        // Modify the scale
        // Convert from real domain to sfml domain
        x = (250 / (scale_x * 1.1f)) * x_real + 250 + (origin_x - 250);
        y = -1 * (250 / (scale_y)) * y_real + 250 + (origin_y - 250);

        // Update the point's position
        p.setPosition(x - 4, y - 4);
    }
    
    points.clear();

    minXCurrent *= 1.1f;
    maxXCurrent *= 1.1f;

    scale_x *= 1.1f;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    points.clear();

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_regression_points[i].position = points[i];
        sfml_regression_points[i].color = sf::Color::Red;
        sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
        sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
    }
}

void Graph::zoomInVertically()
{

    // Update points
    for (sf::CircleShape& p : vectorOfPoints) {
        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        // Modify the scale
        // Convert from real domain to sfml domain
        x = (250 / (scale_x)) * x_real + 250 + (origin_x - 250);
        y = -1 * (250 / (scale_y / 1.1f)) * y_real + 250 + (origin_y - 250);

        // Update the point's position
        p.setPosition(x - 4, y - 4);
    }

    points.clear();

    minYCurrent /= 1.1f;
    maxYCurrent /= 1.1f;

    scale_y /= 1.1f;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    points.clear();

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_regression_points[i].position = points[i];
        sfml_regression_points[i].color = sf::Color::Red;
        sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
        sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
    }
}

void Graph::zoomOutVertically()
{
    // Update points
    for (sf::CircleShape& p : vectorOfPoints) {
        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        // Modify the scale
        // Convert from real domain to sfml domain
        x = (250 / (scale_x)) * x_real + 250 + (origin_x - 250);
        y = -1 * (250 / (scale_y * 1.1f)) * y_real + 250 + (origin_y - 250);

        // Update the point's position
        p.setPosition(x - 4, y - 4);
    }

    points.clear();

    minYCurrent *= 1.1f;
    maxYCurrent *= 1.1f;

    scale_y *= 1.1f;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    points.clear();

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_regression_points[i].position = points[i];
        sfml_regression_points[i].color = sf::Color::Red;
        sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
        sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
    }
}

void Graph::zoomIn()
{
    
    // Update points
    for (sf::CircleShape& p : vectorOfPoints) {
        
        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        // Modify the scale
        // Convert from real domain to sfml domain
        x = (250 / (scale_x / 1.1f)) * x_real + 250 + (origin_x - 250);
        y = -1 * (250 / (scale_y / 1.1f)) * y_real + 250 + (origin_y - 250);

        // Update the point's position
        p.setPosition(x - 4, y - 4);
    }
    
    points.clear();

    minXCurrent /= 1.1f;
    maxXCurrent /= 1.1f;
    minYCurrent /= 1.1f;
    maxYCurrent /= 1.1f;

    scale_x /= 1.1f;
    scale_y /= 1.1f;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    points.clear();

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_regression_points[i].position = points[i];
        sfml_regression_points[i].color = sf::Color::Red;
        sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
        sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
    }
}

void Graph::zoomOut()
{

    // Update points
    for (sf::CircleShape& p : vectorOfPoints) {
        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        // Modify the scale
        // Convert from real domain to sfml domain
        x = (250 / (scale_x * 1.1f)) * x_real + 250 + (origin_x - 250);
        y = -1 * (250 / (scale_y * 1.1f)) * y_real + 250 + (origin_y - 250);

        // Update the point's position
        p.setPosition(x - 4, y - 4);
    }

    points.clear();

    minXCurrent *= 1.1f;
    maxXCurrent *= 1.1f;
    minYCurrent *= 1.1f;
    maxYCurrent *= 1.1f;

    scale_x *= 1.1f;
    scale_y *= 1.1f;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    points.clear();

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_regression_points[i].position = points[i];
        sfml_regression_points[i].color = sf::Color::Red;
        sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
        sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
    }
}

void Graph::reset()
{
    // Update points
    for (sf::CircleShape& p : vectorOfPoints) {

        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        // Modify the scale and origin
        // Convert from real domain to sfml domain
        x = (250 / (10.0f)) * x_real + 250 + (250 - 250);
        y = -1 * (250 / (10.0f)) * y_real + 250 + (250 - 250);

        // Update the point's position
        p.setPosition(x - 4, y - 4);
    }

    points.clear();

    origin_x = 250;
    origin_y = 250;

    old_mouse_x = -1;
    old_mouse_y = -1;

    minXCurrent = -10;
    maxXCurrent = 10;
    minYCurrent = -10;
    maxYCurrent = 10;
    scale_x = 10;
    scale_y = 10;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    // Update the x and y axis
    x_axis[0] = sf::Vertex(sf::Vector2f(0, origin_y));
    x_axis[1] = sf::Vertex(sf::Vector2f(500, origin_y));
    y_axis[0] = sf::Vertex(sf::Vector2f(origin_x, 0));
    y_axis[1] = sf::Vertex(sf::Vector2f(origin_x, 500));

    points.clear();

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_regression_points[i].position = points[i];
        sfml_regression_points[i].color = sf::Color::Red;
        sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
        sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
    }
}

void Graph::drag(sf::RenderWindow& window)
{
    int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;

    if (old_mouse_x == -1 && old_mouse_y == -1) {
        // Initialize the starting position of the mouse
        old_mouse_x = static_cast<float>(x);
        old_mouse_y = static_cast<float>(y);
    }
    else {
        // Compute the x and y deltas
        float delta_x = x - old_mouse_x;
        float delta_y = y - old_mouse_y;
        // Update the previous position of the mouse
        old_mouse_x = static_cast<float>(x);
        old_mouse_y = static_cast<float>(y);
        // Update the origin using the x and y deltas
        origin_x += delta_x;
        origin_y += delta_y;

        // Update the x and y axis
        x_axis[0] = sf::Vertex(sf::Vector2f(0, origin_y));
        x_axis[1] = sf::Vertex(sf::Vector2f(500, origin_y));
        y_axis[0] = sf::Vertex(sf::Vector2f(origin_x, 0));
        y_axis[1] = sf::Vertex(sf::Vector2f(origin_x, 500));

        float real_x = (delta_x / 500) * (maxXCurrent - minXCurrent);
        float real_y = -(delta_y / 500) * (maxYCurrent - minYCurrent);

        maxXCurrent = maxXCurrent - real_x;
        minXCurrent = minXCurrent - real_x;
        maxYCurrent = maxYCurrent - real_y;
        minYCurrent = minYCurrent - real_y;

        points.clear();

        // Real x-axis
        std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

        // Compute real points
        for (auto i : v)
            points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

        // Compute sfml points
        for (size_t i = 0; i < points.size(); i++) {
            sfml_points[i].position = points[i];
            sfml_points[i].color = sf::Color::Green;
            sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
            sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
        }

        // Move the points
        for (sf::CircleShape& p : vectorOfPoints) {
            float x = p.getPosition().x;
            float y = p.getPosition().y;
            x += delta_x;
            y += delta_y;
            p.setPosition(x, y);
        }

        points.clear();

        // Compute real points
        for (auto i : v)
            points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));

        // Compute sfml points
        for (size_t i = 0; i < points.size(); i++) {
            sfml_regression_points[i].position = points[i];
            sfml_regression_points[i].color = sf::Color::Red;
            sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
            sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
        }

    }
}

void Graph::resetMousePosition()
{
    // Resets the mouse position
    old_mouse_x = -1;
    old_mouse_y = -1;
}

void Graph::draw(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setPosition(10, 480);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::White);

    window.draw(y_axis, 2, sf::Lines);
    window.draw(x_axis, 2, sf::Lines);

    if (!postfix.empty()) {
        window.draw(sfml_points);
    }

    if (!coefficient.empty()) {
        window.draw(sfml_regression_points);
    }
    
    float x = static_cast<float>(sf::Mouse::getPosition(window).x);
    float y = static_cast<float>(sf::Mouse::getPosition(window).y);
    x = (x - origin_x) * (scale_x / 250);
    y = (y - origin_y) * (-1 * scale_y / 250);
    std::string coordinate = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    text.setString(coordinate);
    window.draw(text);

    for (sf::CircleShape c : vectorOfPoints) {
        window.draw(c);
    }
}

void Graph::setFunction(std::vector<std::string> postfix)
{
    this->postfix = postfix;
}

void Graph::update()
{
    points.clear();

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

}

void Graph::addPoint(sf::CircleShape c)
{
    vectorOfPoints.push_back(c);
}

void Graph::clearAllPoints()
{
    vectorOfPoints.clear();
    x_mean = 0;
    x_std = 0;
    y_mean = 0;
    y_std = 0;
    coefficient.clear();
}

void Graph::regression(int degree)
{
    std::vector<std::pair<double, double>> target;

    for (sf::CircleShape p : vectorOfPoints) {

        // Get the point's center
        float x = p.getPosition().x + 4;
        float y = p.getPosition().y + 4;

        // Convert from sfml domain to real domain
        float x_real = (x - origin_x) * (scale_x / 250);
        float y_real = (y - origin_y) * (-1 * scale_y / 250);

        target.push_back({ x_real, y_real });

    }

    if (!target.empty()) {

        PolynomialRegression reg;
        reg.setTarget(target);
        std::tie(coefficient, x_mean, x_std, y_mean, y_std) = reg.gradientDescent(degree);

        points.clear();

        // Real x-axis
        std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

        // Compute real points
        for (auto i : v) 
            points.push_back(sf::Vector2f(i, static_cast<float>(polynomial(coefficient, x_mean, x_std, y_mean, y_std, i))));
      
        // Compute sfml points
        for (size_t i = 0; i < points.size(); i++) {
            sfml_regression_points[i].position = points[i];
            sfml_regression_points[i].color = sf::Color::Red;
            sfml_regression_points[i].position.x = (250 / scale_x) * sfml_regression_points[i].position.x + 250 + (origin_x - 250);
            sfml_regression_points[i].position.y = -1 * (250 / scale_y) * sfml_regression_points[i].position.y + 250 + (origin_y - 250);
        }

    }

}

double Graph::polynomial(std::vector<double> coef, double x_m, double x_s, double y_m, double y_s, double i)
{
    
    if (coef.size() == 1) {

        double z = (i - x_mean) / x_std;
        z = coefficient[0];
        z = x_std * z + y_mean;
        return z;

    }
    else if (coef.size() == 2) {

        double z = (i - x_mean) / x_std;
        z = coefficient[0] + coefficient[1] * z;
        z = x_std * z + y_mean;
        return z;

    }
    else if (coef.size() == 3) {

        double z = (i - x_mean) / x_std;
        z = coefficient[0] + coefficient[1] * z + coefficient[2] * pow(z, 2);
        z = x_std * z + y_mean;
        return z;

    }
    else if (coef.size() == 4) {

        double z = (i - x_mean) / x_std;
        z = coefficient[0] + coefficient[1] * z + coefficient[2] * pow(z, 2) + coefficient[3] * pow(z, 3);
        z = x_std * z + y_mean;
        return z;

    }
    else if (coef.size() == 5) {

        double z = (i - x_mean) / x_std;
        z = coefficient[0] + coefficient[1] * z + coefficient[2] * pow(z, 2) + coefficient[3] * pow(z, 3) + coefficient[4] * pow(z, 4);
        z = x_std * z + y_mean;
        return z;

    }
    else if (coef.size() == 6) {

        double z = (i - x_mean) / x_std;
        z = coefficient[0] + coefficient[1] * z + coefficient[2] * pow(z, 2) + coefficient[3] * pow(z, 3) + coefficient[4] * pow(z, 4) + coefficient[5] * pow(z, 5);
        z = x_std * z + y_mean;
        return z;

    }
    else if (coef.size() == 7) { 

        double z = (i - x_mean) / x_std;
        z = coefficient[0] + coefficient[1] * z + coefficient[2] * pow(z, 2) + coefficient[3] * pow(z, 3) + coefficient[4] * pow(z, 4) + coefficient[5] * pow(z, 5) + coefficient[6] * pow(z, 6);
        z = x_std * z + y_mean;
        return z;

    }
    else {

        return 0;

    }

}

Graph::Graph() {

    // Origin of graph (according to SFML)
    origin_x = 250;
    origin_y = 250;

    // Old mouse position -> for dragging/moving the graph
    old_mouse_x = -1;
    old_mouse_y = -1;

    minXCurrent = -10;
    maxXCurrent = 10;
    minYCurrent = -10;
    maxYCurrent = 10;
    scale_x = 10;
    scale_y = 10;

    // SFML points
    sf::VertexArray temp(sf::Points, 100000);
    sfml_points = temp;
    sfml_regression_points = temp;

    // Real x-axis
    std::vector<float> v = linspace(minXCurrent, maxXCurrent, 100000);

    // Compute real points
    for (auto i : v)
        points.push_back(sf::Vector2f(i, static_cast<float>(equation.function(i, postfix))));

    // Compute sfml points
    for (size_t i = 0; i < points.size(); i++) {
        sfml_points[i].position = points[i];
        sfml_points[i].color = sf::Color::Green;
        sfml_points[i].position.x = (250 / scale_x) * sfml_points[i].position.x + 250 + (origin_x - 250);
        sfml_points[i].position.y = -1 * (250 / scale_y) * sfml_points[i].position.y + 250 + (origin_y - 250);
    }

    x_axis[0] = sf::Vertex(sf::Vector2f(0, origin_y));
    x_axis[1] = sf::Vertex(sf::Vector2f(500, origin_y));
    y_axis[0] = sf::Vertex(sf::Vector2f(origin_x, 0));
    y_axis[1] = sf::Vertex(sf::Vector2f(origin_x, 500));

}