#pragma once

#include <vector>
#include <iterator>
#include <memory>

#include "exceptions.h"
#include "cell_reference.h"

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

class PostfixAtom
{
public:
    virtual void evaluate(PostfixStack&) = 0;
    //virtual CellReference get_reference() = 0;
};

class Value: public PostfixAtom
{
private:
    double val;

public:
    Value(double v): val(v) {}
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
    std::unique_ptr<PostfixAtom> atom;

public:
    PostfixElement(std::unique_ptr<PostfixAtom> item): atom(std::move(item)) {}
    void evaluate(PostfixStack&);
};

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

PostfixExpression pure_value(double v);

PostfixElement create_value(double v);

PostfixElement create_operator(char c);
