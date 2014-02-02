#include "cell.h"


Cell::Cell(const std::string &text, const Table &parent_table): original_text(text)
{
    is_dirty = true;

    if (text.length() < 1)
    {
        error_message = "Empty cell";
        error = true;
        expr = pure_value(0);
        return;
    }

    // Single number in cell
    if (text[0] != '=')
    {
        std::stringstream s(text);
        double d;
        // Number parsing failed
        if (!(s >> d))
        {
            error_message = "Invalid number";
            error = true;
            expr = pure_value(0);
            return;
        }
        error = false;
        expr = pure_value(d);
        return;
    }

    // Expression in cell
    {
        try
        {
            expr = parse_infix(text, parent_table, dependencies);
            error = false;
            return;
        }
        catch (InvalidInfixException &e)
        {
            error_message = "Invalid expression";
            error = true;
            expr = pure_value(0);
            return;
        }
    }
}


double Cell::evaluate(std::vector<CellReference> &current_stack)
{

}

