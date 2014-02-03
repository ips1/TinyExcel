#pragma once
#include <string>
#include <memory>
#include <sstream>

#include "table.h"
#include "postfix.h"
#include "cell_reference.h"
//#include "abstract_cell.h"

class Table;

class Cell
{
private:
    bool dirty;
    bool error;
    double value;
    PostfixExpression expr;
    std::vector<CellReference> dependencies;
    std::string original_text;
    std::string error_message;

public:
    bool is_dirty()
    {
        return dirty;
    }
    Cell(const std::string& text, const Table& parent_table);
    void evaluate();
    const double get_value();
    std::vector<CellReference> get_dependencies()
    {
        return dependencies;
    }
};




std::string parse_cell_address(std::string input, int start_pos);
