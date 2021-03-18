#include <iostream>
#include <string>
#include <vector>


// Function to check input expression
bool CheckExpression(std::string exp) {
    for (uint i = 0; i < exp.length(); i++) {
        char c = exp[i];
        if (c < '(' || c > '9' || c == '\'') {
            if (c != ' ') {
                return false;
            }
        }
    }
    return true;
}


// Template function to evaluate atomic expression
template<class T>
T Eval(int a, int b, const char op) {
    switch (op) {
        case '+': {
            return a + b;
        }
        case '-': {
            return a - b;
        }
        case '*': {
            return a * b;
        }
        case '/': {
            return a / b;
        }
        default:
            throw("atomEval: Undefined math operation");
    }
};

// Function to evaluate expression without brackets
template<class T>
std::string EvalExpWithoutBrackets(std::string exp) {
    std::vector<T> operands;
    std::vector<char> operations;
    const uint explen = exp.length();

    // Allocating arguments and operations without ordering
    for (uint shift = 0, position = 0; shift < explen; shift++) {

        // This check need for situation when we didn't allocate last argument
        if (shift == explen - 1) {
            std::string expWithoutBrackets;
            expWithoutBrackets.assign(exp, position, explen - position + 1);
            operands.push_back((T)
            std::stod(expWithoutBrackets));
        }

        if (exp[shift] == '+' || exp[shift] == '-' || exp[shift] == '*' || exp[shift] == '/') {
            std::string expTemp;
            expTemp.assign(exp, position, shift - position);
            operands.push_back((T)std::stod(expTemp));
            operations.push_back(exp[shift]);

            std::string tempExp;
            position = shift + 1;

            for (shift++; shift < explen; shift++) {
                if (exp[shift] == '+' || exp[shift] == '-' || exp[shift] == '*' || exp[shift] == '/') {
                    tempExp.assign(exp, position, shift - position);
                    operations.push_back(exp[shift]);
                    break;
                }

                if (shift == explen - 1) {
                    tempExp.assign(exp, position, explen - position);
                }
            }

            operands.push_back((T)
            std::stod(tempExp));
            position = shift + 1;
        }
    }

    // Calculator
    std::vector<uint> evalOrder; // Order of operations
    uint highPriority = 0;
    uint lowPriority = 0;

    // Ordering operations

    // First of all we need operations with high priority
    for (uint i = 0; i < operations.size(); i++) {
        if (operations[i] == '*' || operations[i] == '/') {
            evalOrder.push_back(i);
            highPriority++;
        }
    }

    // Now we need to order low priority operations
    for (uint i = 0; i < operations.size(); i++) {
        if (operations[i] == '-' || operations[i] == '+') {
            evalOrder.push_back(i);
            lowPriority++;
        }
    }

    // Evaluating epression by order
    for (uint i = 0; i < evalOrder.size(); i++) {
        T rexp = (T) NULL;
        try {
            rexp = Eval<T>(operands[evalOrder[i]], operands[evalOrder[i] + 1], operations[evalOrder[i]]);
        }
        catch(char const *er) {
            std::cout << er << std::endl;
        }

        // Erasing operations and operands, because operands[evalOrder[i]] and operands[evalOrder[i]+1]
        // became single argument after completing operations[evalOrder[i]] operation
        if (evalOrder[i] < operands.size() - 1) {
            operands.erase(operands.begin() + evalOrder[i] + 1);
            operations.erase(operations.begin() + evalOrder[i]);
        }

        // Recallculating order
        for (uint j = i; j < evalOrder.size(); j++) {
            if (evalOrder[j] > evalOrder[i]) {
                evalOrder[j]--;
            }
        }

        // Storing result of eval<T>
        operands[evalOrder[i]] = rexp;
    }

    return std::to_string(operands[0]);
}

template<class T>
std::string EvalExpression(std::string exp) {
    uint open = 0, close = 0;
    for (uint i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') open++;
        else if (exp[i] == ')') close++;
    }
    if (open != close)
        return (std::string) "error: Expression have uncoupled brackets";

    // Divide expression to the blocks if there are any brackets
    for (uint closeBracketPosition = 0; closeBracketPosition < exp.length(); closeBracketPosition++) {
        if (exp[closeBracketPosition] == ')') {
            uint openBracketPosition = closeBracketPosition;

            while (openBracketPosition--) {
                if (exp[openBracketPosition] == '(') {
                    std::string expWithoutBrackets;
                    expWithoutBrackets.assign(
                        exp,
                        /* pos = */ openBracketPosition + 1,
                        /* n = */ closeBracketPosition - openBracketPosition - 1
                    );

                    std::string atomExpResult = EvalExpression<T>(expWithoutBrackets);
                    std::string leftPartExp;
                    std::string rightPartExp;

                    leftPartExp.assign(
                        exp,
                        /* pos = */ 0,
                        /* n = */ openBracketPosition
                    );
                    rightPartExp.assign(
                        exp,
                        /* pos = */ closeBracketPosition + 1,
                        /* n = */ exp.length() - closeBracketPosition
                    );

                    return EvalExpression<T>(leftPartExp + atomExpResult + rightPartExp);
                }
            }
        }
    }
    return EvalExpWithoutBrackets<T>(exp);
}

int main() {

    std::string input;
    std::cin >> input;

    // Check input expression for unhandling symbols
    if (!CheckExpression(input)) {
        return -1;
    }

    // Clear expression from spaces
    for (uint i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            input.erase(input.begin() + i);
            if (i > 0) {
                i--;
            }
        }
    }

    std::cout << "Evaluating expression is: \"" << input << "\"" << std::endl;
    std::cout << "Result is: " << EvalExpression<int>(input) << std::endl;
    return 0;
}