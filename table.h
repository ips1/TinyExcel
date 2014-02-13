#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <memory>
#include <sstream>
#include <exception>
#include <stdexcept>

#include "postfix.h"
#include "cell_reference.h"
#include "parsing.h"

class Table;

class Cell
{
private:
    bool dirty;
    bool error;
    bool on_stack;
    double value;
    PostfixExpression expr;
    std::vector<CellReference> dependencies;
    std::string original_text;
    std::string error_message;

public:
    bool is_dirty() const
    {
        return dirty;
    }
    bool is_on_stack() const
    {
        return on_stack;
    }
    bool put_on_stack()
    {
        on_stack = true;
    }
    bool remove_from_stack()
    {
        on_stack = false;
    }
    const std::string &get_error() const
    {
        return error_message;
    }
    Cell(const std::string& text, Table& parent_table);
    void evaluate();
    void reset();
    double get_value() const;
    const std::vector<CellReference> &get_dependencies() const
    {
        return dependencies;
    }
    std::string get_content() const;
};


// Class for stroring the whole table containing cells
class Table
{
private:
    // Two dimensional map of cells
    std::map<int, std::map<int, Cell>> data;
    // Empty cell for representing all the cells that are not set
    Cell empty_cell;

public:
    void set_cell(const CellReference &t, std::string content);
    Cell &get_cell(const CellReference &t);
    double evaluate_cell(const CellReference &t);

    Table() : empty_cell("0", *this)
    {
        empty_cell.evaluate();
    }
};

class Reference: public PostfixAtom
{
private:
    CellReference target;
    Table &parent_table;

public:
    Reference(const CellReference &t, Table &tab): target(t), parent_table(tab) {}
    virtual void evaluate(PostfixStack&);
};

CellReference coords_to_reference(std::string coords);

PostfixExpression parse_infix(std::string infix, Table &parent_table, std::vector<CellReference> &dependencies);

PostfixElement create_reference(CellReference ref, Table &parent_table);
