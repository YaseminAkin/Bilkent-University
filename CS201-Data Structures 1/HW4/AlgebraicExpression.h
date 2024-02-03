/**
* Title: Stacks
* Author : Yasemin Akın
* ID: 22101782
* Section : 2
* Homework : 4
*/

#ifndef AlgebraicExpression_h
#define AlgebraicExpression_h

#include <stdio.h>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

class AlgebraicExpression {
public:
    
    
    int decide(char c);
};
#endif /* AlgebraicExpression_h */
// It converts an infix expression exp to its equivalent postfix form .
string infix2postfix ( const string exp ) ;
// It evaluates a postfix expression .
double evaluatePostfix ( const string exp ) ;
