#include "Validity.h"

Validity::Validity()
{
}

bool Validity::validTokens(std::string token)
{
    if (valid_string.count(token))
        return true;
    if (isdigit(token[0]) || token[0] == '.')
        return true;
    return false;
}

bool Validity::validParentheses(std::vector<std::string> tokens)
{
    std::stack<std::string> st;

    for (std::string token : tokens) {

        if (token != "(" && token != ")")
            continue;

        if (token == "(")
            st.push(token);
        else { // )
            if (!st.empty() && (st.top() == "(" && token == ")")) {
                st.pop();
            }
            else
                return false;
        }

    }

    return st.empty();
}

bool Validity::isInfixValid(std::vector<std::string> tokens)
{
    // Valid symbols -> "(", ")", "+", "-", "*", "/", "^", "x", "-1", functions, numbers
    for (std::string token : tokens) {
        if (validTokens(token))
            continue;
        else
            return false;
    }

    // Not empty
    if (tokens.empty())
        return false;

    // Balanced parentheses -> (2+3, 2+3))
    if (!validParentheses(tokens))
        return false;

    // (()()) wrong
    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i] == "(") {
            if (i + 1 < tokens.size() && tokens[i + 1] == ")") {
                return false;
            }
        }

    }

    // Has one number or x input
    auto isTheStringNumeric = [](std::string s) -> bool {
        if (isdigit(s[0]) || s[0] == '.')
            return true;
        else
            return false;
    };
    int num_count = 0;
    int x_count = 0;
    for (std::string token : tokens) {

        if (isTheStringNumeric(token))
            num_count++;
        if (token == "x")
            x_count++;

    }
    if (num_count == 0 && x_count == 0)
        return false;

    // function -> (
    // 10cos
    // cos*(x)
    for (int i = 0; i < tokens.size(); i++) {

        if (func.count(tokens[i])) {

            if (i + 1 == tokens.size()) {
                return false; // 10cos
            }

            if (i + 1 < tokens.size() && tokens[i + 1] != "(") {
                return false; // cos* (x)
            }
        }

    }

    // "1++2", 2+*3"
    // "3+"
    // "2+(3-)"
    for (int i = 0; i < tokens.size(); i++) {

        if (oper.count(tokens[i])) {

            if (i + 1 == tokens.size()) {
                return false; // "3+"
            }

            if (i + 1 < tokens.size() && oper.count(tokens[i + 1])) {
                return false; // "1++2", 2+*3"
            }

            if (i + 1 < tokens.size() && tokens[i + 1] == ")") {
                return false; // "2+(3-)"
            }
        }

    }

    // ^2 or *4
    if (!tokens.empty() && oper.count(tokens[0]))
        return false;

    return true;
}