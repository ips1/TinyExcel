#pragma once
#include <stack>
#include "cell.h"
#include "postfix.h"
#include "cell_reference.h"
#include "parsing.h"

class Cell;

class Table
{

public:
    Cell &get_cell(const CellReference &t) const;
    double evaluate_cell(const CellReference &t);
};

class Reference: public PostfixAtom
{
private:
    CellReference target;
    const Table &parent_table;

public:
    Reference(const CellReference &t, const Table &tab): target(t), parent_table(tab) {}
    virtual void evaluate(PostfixStack&);
};

CellReference coords_to_reference(std::string coords);

PostfixExpression parse_infix(std::string infix, const Table &parent_table, std::vector<CellReference> &dependencies);

PostfixElement create_reference(CellReference ref, const Table &parent_table);
