#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <memory>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <ostream>
#include <iostream>

#include "postfix.h"
#include "cell_reference.h"
#include "parsing.h"

// Error messages:
const std::string EVALERR = "Evaluation error";
const std::string DIVERR = "Divide by zero error";
const std::string DEPERR = "Dependency error";
const std::string CYCERR = "Cycle error";
const std::string NUMERR = "Invalid number";
const std::string EXPRERR = "Invalid expression";

// Forward declaration of class table
class Table;

// Class for storing content of one cell
// Because of PostfixExpression included cannot be copied!
class Cell
{
private:
    bool evaluable;
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
    void put_on_stack()
    {
        on_stack = true;
    }
    void remove_from_stack()
    {
        on_stack = false;
    }
    bool has_error() const
    {
        return error;
    }
    const std::string &get_error() const
    {
        return error_message;
    }
    Cell(const std::string& text, Table& parent_table);
    void evaluate();
    void reset();
    void put_on_cycle();
    double get_value() const;
    const std::vector<CellReference> &get_dependencies() const
    {
        return dependencies;
    }
    std::string get_content() const;
    const std::string &get_text() const;
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
    // Copy ctors and assignment operators deleted because of references inside the tables
    // copying would not work with them
    Table(const Table&) = delete;
    Table(Table&&) = delete;
    Table& operator=(const Table&) = delete;
    Table& operator=(Table&&) = delete;

    // Constructor
    Table() : empty_cell("0", *this)
    {
        empty_cell.evaluate();
    }

    // Methods for loading and saving the table, implemented in table_load.cpp
    void load(std::string fname);
    void save(std::string fname, bool original_text);

    void print(std::ostream &out);

    // Methods for cell manipulation
    void set_cell(const CellReference &t, const std::string &content);
    Cell &get_cell(const CellReference &t);

    // Methods for table evaluation and reseting to original state
    void evaluate();
    void reset();

    // Method for evaluating specific cell
    double evaluate_cell(const CellReference &t);

    /*
    const std::map<int, std::map<int, Cell>> &get_data()
    {
        return data;
    }
    */
};

// Postfix extension which provides references (links) to cells
class Reference: public PostfixAtom
{
private:
    CellReference target;
    Table &parent_table;

public:
    Reference(const CellReference &t, Table &tab): target(t), parent_table(tab) {}
    virtual void evaluate(PostfixStack&);
};

// Additional global functions for table and postfix handling

CellReference coords_to_reference(const std::string &coords);

PostfixExpression parse_infix(const std::string &infix, Table &parent_table, std::vector<CellReference> &dependencies);

PostfixElement create_reference(CellReference r, Table &parent_table);

#endif // TABLE_H
