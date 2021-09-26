/**
 * @file interpreter.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <typeinfo>

using namespace std;

class Expression {
public:
    virtual ~Expression() {}
    virtual int interpreter(map<string, int> &var) = 0;
};

class VarExpression : public Expression {
private:
    string key;

public:
    VarExpression(string key) {
        this->key = key;
    }

    int interpreter(map<string, int> &var) {
        return var[key];
    }

    ~VarExpression() {
        cout << "~VarExression()" << endl;
    }
};

class SymbolExpression : public Expression {
protected:
    Expression *left;
    Expression *right;

public:
    SymbolExpression(Expression *left, Expression *right) {
        this->left = left;
        this->right = right;
    }

    Expression* getLeft() {
        return this->left;
    }

    Expression* getRight() {
        return this->right;
    }
};

class AddExpression : public SymbolExpression {
public:
    AddExpression(Expression *left, Expression *right) : SymbolExpression(left, right) {}

    int interpreter(map<string, int> &var) {
        return left->interpreter(var) + right->interpreter(var);
    }
    ~AddExpression() {
        cout << "~AddExpression()" << endl;
    }
};

class SubExpression : public SymbolExpression {
public:
    SubExpression(Expression *left, Expression *right) : SymbolExpression(left, right) {}

    int interpreter(map<string, int> &var) {
        return left->interpreter(var) - right->interpreter(var);
    }
    ~SubExpression() {
        cout << "~SubExpress()" << endl;
    }
};

class Calculator {
private:
    Expression* expression;

public:
    Calculator(string expStr) {
        expression = nullptr;

        stack<Expression*> stkExp;

        Expression *left = nullptr, *right = nullptr;

        for (auto i = 0; i < expStr.length(); ++i) {
            switch(expStr[i]) {
                case '+' :
                    left = stkExp.top(); stkExp.pop();
                    right = new VarExpression(expStr.substr(++i, 1));
                    stkExp.push(new AddExpression(left, right));
                    break;
                case '-':
                    left = stkExp.top(); stkExp.pop();
                    right = new VarExpression(expStr.substr(++i, 1));
                    stkExp.push(new SubExpression(left, right));
                    break;
                default:
                    stkExp.push(new VarExpression(expStr.substr(i,1)));
            }
        }
        if (!stkExp.empty()) {
            expression = stkExp.top(); stkExp.pop();
        }
    }

    void deltree(Expression *expression) {
        SymbolExpression *banch = dynamic_cast<SymbolExpression*>(expression);

        if (banch == nullptr)
            delete expression;
        else {
            deltree(banch->getLeft());
            deltree(banch->getRight());
            delete expression;
        }
    }

    ~Calculator() {
        deltree(expression);
        expression = nullptr;
    }

    int run(map<string, int> &var) {
        return (expression == nullptr) ? 0 : expression->interpreter(var);
    }
};

int main () {
    string expStr = "a+b-c";

    map<string, int> var;
    var["a"] = 100;
    var["b"] = 20;
    var["c"] = 40;

    Calculator cal(expStr);

    cout << "result: " << expStr << " = " << cal.run(var) << endl;

    return 0;
}