#pragma once
#include <string>
#include <memory>
#include <sstream>

#include "postfix.h"
#include "table.h"
#include "cell_reference.h"
//#include "abstract_cell.h"

class Table;

class Cell
{
private:
    bool is_dirty;
    bool error;
    double cache;
    PostfixExpression expr;
    std::vector<CellReference> dependencies;
    std::string original_text;
    std::string error_message;

public:
    Cell(const std::string& text, const Table& parent_table);
    double evaluate(std::vector<CellReference> &current_stack);
    std::vector<CellReference> get_dependencies()
    {
        return dependencies;
    }
};




std::string parse_cell_address(std::string input, int start_pos);
