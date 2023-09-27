#include "Equation.h"

Equation::Equation() {

}

double Equation::function(double x, std::vector<std::string> postfix) {

    if (postfix.empty())
        return 0;

    std::stack<double> s;
    
    for (std::string t : postfix) {

        if (t == "+") {

            double second = s.top();
            s.pop();
            double first = s.top();
            s.pop();
            s.push(first + second);

        }
        else if (t == "-") {

            double second = s.top();
            s.pop();
            double first = s.top();
            s.pop();
            s.push(first - second);

        }
        else if (t == "*") {

            double second = s.top();
            s.pop();
            double first = s.top();
            s.pop();
            s.push(first * second);
        }
        else if (t == "/") {

            double second = s.top();
            s.pop();
            double first = s.top();
            s.pop();
            s.push(first / second);

        }
        else if (t == "^") {

            double second = s.top();
            s.pop();
            double first = s.top();
            s.pop();
            s.push(pow(first, second));

        }
        else if (t == "abs") {

            double num = s.top();
            s.pop();
            s.push(abs(num));

        }
        else if (t == "exp") {

            double num = s.top();
            s.pop();
            s.push(exp(num));

        }
        else if (t == "ln") {
            
            double num = s.top();
            s.pop();
            s.push(log(num));

        }
        else if (t == "log") {
            
            double num = s.top();
            s.pop();
            s.push(log10(num));

        }
        else if (t == "sgn") {
           
            double num = s.top();
            s.pop();
            s.push(sgn(num));

        }
        else if (t == "sinc") {

            double num = s.top();
            s.pop();
            s.push(sinc(num));

        }
        else if (t == "csc") {
            
            double num = s.top();
            s.pop();
            s.push(csc(num));

        }
        else if (t == "sec") {

            double num = s.top();
            s.pop();
            s.push(sec(num));

        }
        else if (t == "cot") {
            
            double num = s.top();
            s.pop();
            s.push(cot(num));

        }
        else if (t == "arctan") {
            
            double num = s.top();
            s.pop();
            s.push(atan(num));

        }
        else if (t == "arccos") {

            double num = s.top();
            s.pop();
            s.push(acos(num));

        }
        else if (t == "arcsin") {

            double num = s.top();
            s.pop();
            s.push(asin(num));

        }
        else if (t == "sinh") {

            double num = s.top();
            s.pop();
            s.push(sinh(num));

        }
        else if (t == "cosh") {

            double num = s.top();
            s.pop();
            s.push(cosh(num));

        }      
        else if (t == "tanh") {

            double num = s.top();
            s.pop();
            s.push(tanh(num));

        }
        else if (t == "sin") {

            double num = s.top();
            s.pop();
            s.push(sin(num));

        }
        else if (t == "cos") {

            double num = s.top();
            s.pop();
            s.push(cos(num));

        }
        else if (t == "tan") {

            double num = s.top();
            s.pop();
            s.push(tan(num));

        }
        else if (t == "factorial") {

            double num = s.top();
            s.pop();
            s.push(factorial(num));

        }
        else if (t == "sqrt") {

            double num = s.top();
            s.pop();
            s.push(sqrt(num));

        }
        else { // The token is a number

            if(t == "x")
                s.push(x);
            else
                s.push(stod(t));
         
        }
            
    }

    return s.top();
    
}

double Equation::factorial(double x) {
    return tgamma(x + 1);
}

int Equation::sgn(double x)
{
    if (x < 0)
        return -1;
    else if (x == 0)
        return 0;
    else
        return 1;
}

double Equation::sinc(double x)
{
    if (x == 0)
        return 1;
    else
        return sin(x) / x;
}

double Equation::cot(double x)
{
    if (tan(x) != 0)
        return 1 / tan(x);
    else
        return INT_MAX;
}

double Equation::sec(double x)
{
    if (cos(x) != 0)
        return 1 / cos(x);
    else
        return INT_MAX;
}

double Equation::csc(double x)
{
    if (sin(x) != 0)
        return 1 / sin(x);
    else
        return INT_MAX;
}