// ifn - infix notation (normal)
// rpn - reverse polish notation (not normal)
#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <sstream>

using namespace std;

bool isBracket (char c)
{
    return (c == '(' || c == ')');
}
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
int getPrecedence(char c)
{
    if (c == '+' || c == '-')
        return 0;
    else if (c == '*' || c == '/')
        return 1;
    else if (c == '^')
        return 2;
    return -1;
}

string convert_ifn_to_rpn(string operation)
{
    string output;
    stack <char> operator_stack;
    string actual_num;

    for (char symbol : operation)
    {

        if (isOperator(symbol))
        {
            while (!operator_stack.empty() && !isBracket(symbol) &&
            ( ( symbol == '^' && getPrecedence(symbol) < getPrecedence(operator_stack.top()) ) || symbol != '^' && getPrecedence(symbol) <= getPrecedence(operator_stack.top()) ))
            {
                output += operator_stack.top(); output += ' ';
                operator_stack.pop();
            }
            operator_stack.push(symbol);
        }

        else if (symbol == '(')
            operator_stack.push('(');
        
        else if (symbol == ')')
        {
            do {
                output += operator_stack.top(); output += ' ';
                operator_stack.pop(); 
            } while(operator_stack.top() != '(');
            operator_stack.pop();
        }

        else if (symbol == ' ')
        {
            if (!actual_num.empty())
            {
                output += actual_num; output += ' ';
                actual_num = {};
            }
        }

        else
            actual_num += symbol;
    }
    if (!actual_num.empty())
    {
        output += actual_num; output += ' ';
    }
    while (!operator_stack.empty())
    {
        output += operator_stack.top(); output += ' ';
        operator_stack.pop();
    }

    return output;

}

double calculate_rpn(string operation)
{
    stack <double> output_stack;

    string actual_num;

    for (char symbol : operation)
    {
        if (isOperator(symbol))
        {
            double num1 = output_stack.top(); output_stack.pop();
            double num2 = output_stack.top(); output_stack.pop();

            double result;
            switch(symbol) {
                case '+':
                 result = num2 + num1;
                 break;
                case '-':
                 result = num2 - num1;
                 break;
                case '*':
                 result = num2 * num1;
                 break;
                case '/':
                 result = num2 / num1;
                 break;
                case '^':
                 result = pow(num2, num1);
                 break;
            }
            output_stack.push(result);
            actual_num = {};
        }
        else if (symbol == ' ' && !actual_num.empty())
        {
            double result;
            stringstream(actual_num) >> result;
            output_stack.push(result);
            actual_num = {};
        }
        else
            actual_num += symbol;
    };
    return output_stack.top();
}
int main()
{
    string user_input_operation;
    // user_input_operation = "12 2 3 4 * 10 5 / + * +";
    // user_input_operation = "1 2 + 4 * 5 + 3 -";
    // user_input_operation = "3 4 2 * 1 5 - 2 ^ / +";
    // user_input_operation = "5 + 2 * 4 / ( 2 - 5 )";
    // user_input_operation = "3 + 4 * 2 / ( 1 - 5 ) ^ 2";


    cout << endl << "program automatically detect which system you typed. (just dont use spaces at the end)" << endl << endl;
    cout << endl << "type operation (use spaces between every number and symbol): ";
    getline(cin, user_input_operation);

    string rpn_operation;

    if (!isOperator(user_input_operation.back()))
        rpn_operation = convert_ifn_to_rpn(user_input_operation);
    else
         rpn_operation = user_input_operation;

    cout << endl << "RPN notation: " << rpn_operation << endl;
    cout << "result: " << calculate_rpn(rpn_operation) << endl;

    cout << endl << endl << "press enter to quit." << endl;
    getchar();
    return 0;
}
