#include "Lexer.h"

Lexer::Lexer()
{
}

std::vector<std::string> Lexer::getTokens(std::string equation)
{
    std::vector<std::string> tokens;

    std::string token;
    for (int i = 0; i < equation.size(); i++) {

        char c = equation[i];
        if (isspace(c))
            continue;
        if (c == 'x') {
            tokens.push_back("x");
            continue;
        }
        if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '(' || c == ')') {
            tokens.push_back(std::string() + c);
            continue;
        }
        if (isalpha(c)) {
            token += c;
            while (i + 1 < equation.size() && isalpha(equation[i + 1])) {
                i++;
                token += equation[i];
            }
            tokens.push_back(token);
            token.clear();
            continue;
        }
        if (isdigit(c) || c == '.') {
            token += c;
            while (i + 1 < equation.size() && (isdigit(equation[i + 1]) || equation[i + 1] == '.')) {
                i++;
                token += equation[i];
            }
            tokens.push_back(token);
            token.clear();
            continue;
        }

    }

    // Fix unary (minus) sign

    // First tokem is (-)
    // -(x^2)
    if (tokens[0] == "-" && tokens.size() > 1) {
        tokens[0] = "-1";
        tokens.insert(tokens.begin() + 1, "*");
    }

    // (-) after +,-,/,*,^,(
    // 3+-2
    // 3--2
    // 3/-2
    // 3*-2
    // 3^-2
    // 2*(-2+2)
    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "/" || tokens[i] == "*" || tokens[i] == "^" || tokens[i] == "(") {

            if (i + 2 < tokens.size() && tokens[i + 1] == "-") {

                tokens[i + 1] = "-1";
                tokens.insert(tokens.begin() + i + 2, "*");
                tokens.insert(tokens.begin() + i + 1, "(");
                tokens.insert(tokens.begin() + i + 5, ")");

            }

        }

    }

    // 10cos(x) -> "10", "*", "cos", "(", "x", ")"
    // .8cos(x) -> ".8", "*", "cos", "(", "x", ")"

    // 10x 
    // 10(x)
    // 10(

    // ERRORS -> 10), 10+, 10-, 10*, 10/, 10^

    auto isTheStringNumeric = [](std::string s) -> bool {
        if (isdigit(s[0]) || s[0] == '.')
            return true;
        else
            return false;
    };

    for (int i = 0; i < tokens.size(); i++) {

        if (isTheStringNumeric(tokens[i])) {
            if (i + 1 < tokens.size() && !isTheStringNumeric(tokens[i + 1]) && tokens[i + 1] != ")" && tokens[i + 1] != "+" && tokens[i + 1] != "-" && tokens[i + 1] != "*" && tokens[i + 1] != "/" && tokens[i + 1] != "^") {
                tokens.insert(tokens.begin() + i + 1, "*");
            }
        }

    }

    // (10)x, (10)(x)
    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i] == ")") {
            if (i + 1 < tokens.size() && (tokens[i + 1] == "x" || tokens[i + 1] == "(")) {
                tokens.insert(tokens.begin() + i + 1, "*");
            }
        }

    }

    // xx, x(x)
    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i] == "x") {
            if (i + 1 < tokens.size() && (tokens[i + 1] == "x" || tokens[i + 1] == "(")) {
                tokens.insert(tokens.begin() + i + 1, "*");
            }
        }

    }

    //xcos(x)
    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i] == "x") {
            if (i + 1 < tokens.size() && func.contains(tokens[i+1])) {
                tokens.insert(tokens.begin() + i + 1, "*");
            }
        }

    }

    // cos(x)cos(x)
    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i] == ")") {
            if (i + 1 < tokens.size() && func.contains(tokens[i + 1])) {
                tokens.insert(tokens.begin() + i + 1, "*");
            }
        }

    }

    // Ambiguous
    // x^2tan(x) = ["x", "^", "2", "*", "tan", "(", "x", ")"]
    // 2^2x = ["2", "^", "2", "*", "x"]

    return tokens;

}