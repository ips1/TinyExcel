#ifndef POSTFIX_H
#define POSTFIX_H

#include <vector>
#include <memory>

#include "exceptions.h"
#include "cell_reference.h"

// Stack for postfix evaluation
// - stores the numbers
class PostfixStack
{
private:
    std::vector<double> data;
public:
    void push(double new_item)
    {
        data.push_back(new_item);
    }

    double pop()
    {
        if (data.size() < 1) throw InvalidPostfixException();
        double ret = data.back();
        data.pop_back();
        return ret;
    }

    int size()
    {
        return data.size();
    }
};

// Abstract class for a part of postfix expression
class PostfixAtom
{
public:
    // Abstract method retrieving the value of the atom
    virtual void evaluate(PostfixStack&) = 0;
};

// -- Subclassees specifiing types of postfix atoms

class Value: public PostfixAtom
{
private:
    double val;

public:
    Value(double v): val(v) {}
    virtual void evaluate(PostfixStack&);
};

class UnaryOperator: public PostfixAtom
{
public:
    virtual void evaluate(PostfixStack&) = 0;
};

class Negation: public PostfixAtom
{
public:
    virtual void evaluate(PostfixStack&);
};

class BinaryOperator: public PostfixAtom
{
public:
    virtual void evaluate(PostfixStack&) = 0;

};

class Addition: public BinaryOperator
{
public:
    virtual void evaluate(PostfixStack&);
};


class Subtraction: public BinaryOperator
{
public:
    virtual void evaluate(PostfixStack&);
};


class Multiplication: public BinaryOperator
{
public:
    virtual void evaluate(PostfixStack&);
};


class Division: public BinaryOperator
{
public:
    virtual void evaluate(PostfixStack&);
};

// Wrapper class for PostfixAtoms unique pointers
class PostfixElement
{
private:
    std::shared_ptr<PostfixAtom> atom;

public:
	PostfixElement(std::shared_ptr<PostfixAtom> item) : atom(item) {}
    void evaluate(PostfixStack&);
};

// Class for holding entire postfix expression
// - consists of PostfixAtoms unique pointers wrapped in PostfixElement
class PostfixExpression
{
private:
    std::vector<PostfixElement> data;

public:
    //PostfixExpression(const PostfixExpression&) = delete;
    void add_element(PostfixElement new_element)
    {
        data.push_back(std::move(new_element));
    }
    double evaluate();
};

// Classes for creating specific expressions and elements
PostfixExpression pure_value(double v);

PostfixElement create_value(double v);

PostfixElement create_operator(char c);


#endif // POSTFIX_H
