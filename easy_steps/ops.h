class Calculator {
public:
    Calculator();           // to set the initial status
    void launch();          // to display the instructions
    void readInput();       // to get the expression
    void writeOutput();     // to display the result
    bool run();             // to get the current status

private:
    double num1, num2;      // to store the input numbers
    char oper;              // to store the input operator
    bool status;            // to store the current status
};

