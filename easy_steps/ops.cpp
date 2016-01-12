#include "../easy_steps/ops.h"

#include <iostream>

using namespace std;

// Initialse the status
Calculator::Calculator() :status(true) { }

// Display instructions
void Calculator::launch() {
    cout << "Enter a number, an operator (+ - * /) and another number." << endl;
    cout << "Hit return to calculate. Enter 0 to exit." << endl;
}

// Get the expression
void Calculator::readInput() {
    cout << "> ";       // get the 1st number
    cin >> num1;
    if(num1 == 0) {     // exit if it is 0
        status = false;
    }
    else {              // get the operator and the 2nd number
        cin >> oper;
        cin >> num2;
    }
}

// Display the result
void Calculator::writeOutput() {
    if(status) {
        switch(oper) {
        case '+':
            cout << (num1 + num2) << endl;
            break;

        case '-':
            cout << (num1 - num2) << endl;
            break;

        case '*':
            cout << (num1 * num2) << endl;
            break;

        case '/':
            if(num2 != 0) {
                cout << (num1 / num2) << endl;
            }
            else {
                cout << "Cannot divide by zero" << endl;
            }
            break;
        }
    }
}

bool Calculator::run() {
    return status;
}

