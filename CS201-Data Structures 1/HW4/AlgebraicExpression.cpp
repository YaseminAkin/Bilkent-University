/**
* Title: Stacks
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 4
*/

#include "AlgebraicExpression.h"

int AlgebraicExpression::decide(char c) {
    if (c == '*' || c == '/') {
        return 999;
    }
    else if (c == '+' || c == '-') {
        return 111;
    }
    else {
        return 0;
    }
}

string infix2postfix ( const string exp ) {
    AlgebraicExpression ae;
    stack<char> newStack;
    string postfix;

    for (char c : exp) {
        if (c == ' ') {
            continue;
        }
        else if (isdigit(c)) {
            postfix += c;
        }
        else if (c == '(') {
            newStack.push(c);
        }
        else if (c == ')') {
            while (!newStack.empty() && newStack.top() != '(') {
                postfix += newStack.top();
                newStack.pop();
            }
            newStack.pop();
        }
        else {
            while (!newStack.empty() && newStack.top() != '(' &&
                   ae.decide(c) <= ae.decide(newStack.top())) {
                postfix += newStack.top();
                newStack.pop();
            }
            newStack.push(c);
        }
    }
    while (!newStack.empty()) {
        postfix += newStack.top();
        newStack.pop();
    }
    return postfix;
}

double evaluatePostfix ( const string exp ) {
    stack<double> newStack;
    for (char c : exp) {
        if (c == ' ') {
            continue;
        }
        else if (isdigit(c)) {
            double operand = c - '0';
            newStack.push(operand);
        }
        else {
            double operand2 = newStack.top();
            newStack.pop();
            double operand1 = newStack.top();
            newStack.pop();
            double result;
            switch (c) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    return 0;
            }
            newStack.push(result);
        }
    }
    return newStack.top();
}
