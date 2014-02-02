// UNUSED FILE
// Warning!
// This file is NOT used in the project
// Kept just for archiving!




#include <memory>
#include <vector>
#include "table.h"

class Expression
{
public:
    virtual double evaluate() = 0;
};

class Value: public Expression
{
private:
    double val;

public:
    Value(double v): val(v) {}
    virtual double evaluate();

};

class Reference: public Expression
{
private:
    CellReference target;

public:
    Reference(CellReference t): target(t) {}
    virtual double evaluate();
};

class BinaryOperator: public Expression
{
protected:
    std::unique_ptr<Expression> left_operand;
    std::unique_ptr<Expression> right_operand;

public:
    BinaryOperator(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right): left_operand(std::move(left)), right_operand(std::move(right)) {}
    virtual double evaluate() = 0;

};

class Addition: public BinaryOperator
{
public:
    Addition(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right): BinaryOperator(std::move(left), std::move(right)) {}
    virtual double evaluate();
};


class Subtraction: public BinaryOperator
{
public:
    Subtraction(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right): BinaryOperator(std::move(left), std::move(right)) {}
    virtual double evaluate();
};


class Multiplication: public BinaryOperator
{
public:
    Multiplication(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right): BinaryOperator(std::move(left), std::move(right)) {}
    virtual double evaluate();
};


class Division: public BinaryOperator
{
public:
    Division(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right): BinaryOperator(std::move(left), std::move(right)) {}
    virtual double evaluate();
};


class InfixParser
{
private:
    std::vector<std::string> tmp_postfix;
    void infix_to_postfix(std::string infix);
    std::unique_ptr<Expression> postfix_to_tree();

public:
    std::unique_ptr<Expression> build_expression_tree(std::string infix);

};


