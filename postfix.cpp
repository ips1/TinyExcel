#include <iostream>
#include "postfix.h"

void PostfixElement::evaluate(PostfixStack& current_stack)
{
    atom->evaluate(current_stack);
}

void Value::evaluate(PostfixStack& current_stack)
{
    current_stack.push(this->val);
}

void Addition::evaluate(PostfixStack& current_stack)
{
    double first = current_stack.pop();
    double second = current_stack.pop();

    current_stack.push(second + first);
}

void Subtraction::evaluate(PostfixStack& current_stack)
{
    double first = current_stack.pop();
    double second = current_stack.pop();

    current_stack.push(second - first);
}

void Multiplication::evaluate(PostfixStack& current_stack)
{
    double first = current_stack.pop();
    double second = current_stack.pop();

    current_stack.push(second * first);
}

void Division::evaluate(PostfixStack& current_stack)
{
    double first = current_stack.pop();
    double second = current_stack.pop();

    if (first == 0) throw DivideByZeroException();

    current_stack.push(second / first);
}

double PostfixExpression::evaluate()
{
    PostfixStack current_stack;

    if (data.size() < 1) throw InvalidPostfixException();

    for (auto it = data.begin(); it < data.end(); ++it)
    {
        it->evaluate(current_stack);
    }

    if (current_stack.size() != 1) throw InvalidPostfixException();

    return current_stack.pop();
}


PostfixExpression pure_value(double v)
{
    PostfixExpression expr;
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Value(v)))));
    return std::move(expr);
}

PostfixElement create_value(double v)
{
    return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Value(v))));
}

PostfixElement create_operator(char c)
{
    switch (c)
    {
        case '+': return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Addition)));
        case '-': return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Subtraction)));
        case '*': return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Multiplication)));
        case '/': return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Division)));
        default: throw InvalidOperatorException();
    }
}

