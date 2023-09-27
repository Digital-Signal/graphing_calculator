#include <SFML/Graphics.hpp>

#include "ShuntingYardAlgorithm.h"
#include "Graph.h"
#include "Validity.h"
#include "Lexer.h"

#include <iostream>
#include <sstream>
#include <unordered_set>
#include <stack>
#include <chrono>
#include <iomanip>
#include <ctime>

#include <time.h>

// Helper Functions
bool valid_input(int code) {

    switch (code) {
        case 40: case 41: case 42: case 43: case 45: case 46: case 47: case 48: case 49: 
        case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57: case 94: 
        case 127: case 97: case 98: case 99: case 101: case 102: case 103: case 104: case 105:
        case 108: case 110: case 111: case 112: case 113: case 114: case 115: case 116: case 120:
        return true;
    default:
        return false;
    }

}

int main() {

    sf::RenderWindow window(sf::VideoMode(1000, 500), "Graphing Calculator", sf::Style::Close);
    window.setFramerateLimit(60);

    Graph graph;

    //-----------------------------------------------------------------------------------------------------

    sf::RectangleShape menu(sf::Vector2f(500, 500));
    menu.setPosition(500, 0);
    menu.setFillColor(sf::Color(100, 100, 100));

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
    {
        exit(-1);
    }
    sf::Text text_controls;
    text_controls.setFont(font);
    text_controls.setCharacterSize(18);
    text_controls.setFillColor(sf::Color::White);
    text_controls.setString(
                            "LControl + Mouse Wheel Scroll = Zoom In/Out Horizontally\n"
                            "LShift + Mouse Wheel Scroll = Zoom In/Out Vertically\n"
                            "Mouse Wheel Scroll = Zoom In/Out\n"
                            "Left Click And Drag = Change The View\n"
                            "Escape = Reset The View\n"
                            "Right Click = Add A Point\n"
                            "Space Bar = Erase All Points\n"
                            "Tab = Take A Screenshot\n"
                            "Enter + 0 = Polynomial Regression Model (Degree 0)\n"
                            "Enter + 1 = Polynomial Regression Model (Degree 1)\n"
                            "Enter + 2 = Polynomial Regression Model (Degree 2)\n"
                            "Enter + 3 = Polynomial Regression Model (Degree 3) [SLOW]\n"
                            "Enter + 4 = Polynomial Regression Model (Degree 4) [SLOW]\n"
                            "Enter + 5 = Polynomial Regression Model (Degree 5) [SLOW]\n"
                            "Enter + 6 = Polynomial Regression Model (Degree 6) [SLOW]\n"
                            "\nValid Inputs: \n"
                            "x, (, ), +, -, *, /, ^\n"
                            "abs, exp, ln, log, sgn, sinc, csc, sec, cot\n"
                            "arctan, arccos, arcsin, sinh, cosh, tanh\n"
                            "sin, cos, tan, factorial, sqrt"
                           );
    text_controls.setPosition(508, 10);

    sf::Text text_equation;
    text_equation.setFont(font);
    text_equation.setCharacterSize(20);
    text_equation.setFillColor(sf::Color::Green);
    text_equation.setPosition(510, 470);
    text_equation.setString("y = f(x) = ");

    //-----------------------------------------------------------------------------------------------------

    std::string string_equation;

    int skip = 0; // Ignores regression choice

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
                
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    
                    if (event.mouseWheel.delta >= 1)  // Zoom in horizontally
                        graph.zoomInHorizontally();
                    else  // Zoom out horizontally
                        graph.zoomOutHorizonatlly();

                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                   
                    if (event.mouseWheel.delta >= 1) // Zoom in vertically
                        graph.zoomInVertically();
                    else  // Zoom out vertically
                        graph.zoomOutVertically();

                }
                else {

                    if (event.mouseWheel.delta >= 1)  // Zoom in
                        graph.zoomIn();
                    else  // Zoom out
                        graph.zoomOut();

                }
            }
            
            if (event.type == sf::Event::TextEntered)
            {
                // Get the Unicode value of the character
                sf::Uint32 unicode = event.text.unicode;
       
                if (unicode == 13) skip = 2; // Ignores regression choice
                if (skip == 0) {

                    // If it is a printable character, append it to the input string
                    if (valid_input(unicode))
                        string_equation += static_cast<char>(unicode);

                    // If it is the backspace key, erase the last character
                    if (unicode == 8 && !string_equation.empty())
                        string_equation.pop_back();

                    // Update the text with the input string
                    text_equation.setString("y = f(x) = " + string_equation);

                    if (!string_equation.empty()) {

                        Validity v;
                        Lexer l;
                        ShuntingYardAlgorithm s;
                        std::vector<std::string> postfix;

                        std::vector<std::string> tokens = l.getTokens(string_equation);

                        if (v.isInfixValid(tokens)) { // Function is valid

                            postfix = s.infixToPostfix(tokens);
                            graph.setFunction(postfix); 
                            graph.update();

                        }
                        else { // Function is invalid

                            graph.setFunction(std::vector<std::string>());
                            graph.update();

                        }

                    }
                    else { // No input
                        graph.setFunction(std::vector<std::string>());
                        graph.update();
                    }

                }
                if(skip != 0) skip--; // Ignores regression choice
                
            }
            
            if (event.type == sf::Event::KeyPressed) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                    
                    sf::Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    sf::Image screenshot = texture.copyToImage();

                    std::time_t now = std::time(nullptr); 
                    std::string file_name = std::to_string(now) + ".png";

                    std::cout << '\a';
                    screenshot.saveToFile(file_name);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    graph.reset();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    graph.clearAllPoints();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) 
                        graph.regression(0);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) 
                        graph.regression(1);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) 
                        graph.regression(2);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) 
                        graph.regression(3);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) 
                        graph.regression(4);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) 
                        graph.regression(5);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) 
                        graph.regression(6);

                }
                   
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {

                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;

                    if ((x >= 4 && x <= 496) && (y >= 4 && y <= 496)) {

                        sf::CircleShape circle(4);
                        circle.setPosition(static_cast<float>(event.mouseButton.x - 4), static_cast<float>(event.mouseButton.y - 4));
                        circle.setFillColor(sf::Color(3, 177, 252));
                        graph.addPoint(circle);

                    }

                }
            }
 
        }
  
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            graph.drag(window);
        else
            graph.resetMousePosition();

        // ---------------------------------------------------------------------------------------------------

        window.clear(sf::Color(0, 0, 0));

        graph.draw(window);
        window.draw(menu);
        window.draw(text_controls);
        window.draw(text_equation);

        window.display();

        // ---------------------------------------------------------------------------------------------------
    }

    return 0;
}