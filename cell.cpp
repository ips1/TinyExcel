#include <sstream>

#include "table.h"
#include "exceptions.h"


Cell::Cell(const std::string &text, Table &parent_table): original_text(text)
{
    dirty = true;
    evaluable = true;

    if (text.length() < 1)
    {
        error = false;
        dirty = false;
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
            dirty = false;
            error = true;
            evaluable = false;
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
            std::string new_text = text.substr(1, text.length() - 1);
            expr = parse_infix(new_text, parent_table, dependencies);
            error = false;
            return;
        }
        catch (InvalidInfixException &e)
        {
            error_message = "Invalid expression";
            dirty = false;
            error = true;
            evaluable = false;
            expr = pure_value(0);
            return;
        }
    }
}


void Cell::evaluate()
{
    // Assume that all dependencies have been properly evaluated
    // otherwise throws EvaluationException

    if (!evaluable) return;
    if (!dirty) return;

    value = 0;
    error = false;
    error_message = "";

    try
    {
        double res = expr.evaluate();
        value = res;
    }
    catch (InvalidOperatorException &ex)
    {
        error = true;
        error_message = EVALERR;
    }
    catch (InvalidPostfixException &ex)
    {
        error = true;
        error_message = EVALERR;
    }
    catch (DivideByZeroException &ex)
    {
        error = true;
        error_message = DIVERR;
    }
    catch (DependencyException &ex)
    {
        error = true;
        error_message = DEPERR;
    }

    dirty = false;
}

double Cell::get_value() const
{
    return value;
}

void Cell::reset()
{
    if (!evaluable) return;

    error = false;
    error_message = "";
    dirty = true;
    value = 0;
}

void Cell::put_on_cycle()
{
    if (!evaluable) return;
    error = true;
    error_message = CYCERR;
    dirty = false;
    value = 0;
}

std::string Cell::get_content() const
{
    if (error)
    {
        return error_message;
    }
    if (dirty)
    {
        return "Not evaluated";
    }
    std::stringstream ss;
    ss << value;
    return ss.str();
}

const std::string &Cell::get_text() const
{
    return original_text;
}

