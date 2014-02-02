// UNUSED FILE
// Warning!
// This file is NOT used in the project
// Kept just for archiving!




#include "expression.h"

#include <iostream>

double Value::evaluate()
{
    return val;
}

double Reference::evaluate()
{
    return target.getValue();
}

double Addition::evaluate()
{
    return (left_operand->evaluate() + right_operand->evaluate());
}

double Subtraction::evaluate()
{
    return (left_operand->evaluate() - right_operand->evaluate());
}

double Multiplication::evaluate()
{
    return (left_operand->evaluate() * right_operand->evaluate());
}

double Division::evaluate()
{
    return (left_operand->evaluate() / right_operand->evaluate());
}

