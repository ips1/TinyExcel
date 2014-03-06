#include <sstream>

#include "table.h"
#include "exceptions.h"

// Cell constructor, parses string specifiing the cell content
Cell::Cell(const std::string &text, Table &parent_table): original_text(text)
{
    dirty = true;
    evaluable = true;
    on_stack = false;

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
		bool failed = false;
        // Number parsing failed
		if (!(s >> d)) failed = true;
		if (s.rdbuf()->in_avail() != 0) failed = true;

		if (failed)
        {
            error_message = NUMERR;
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
            error_message = EXPRERR;
            dirty = false;
            error = true;
            evaluable = false;
            expr = pure_value(0);
            return;
        }
    }
}

// Evaluates a single cell (if it is dirty and evaluable)
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
        error_message = EXPRERR;
    }
    catch (InvalidPostfixException &ex)
    {
        error = true;
        error_message = EXPRERR;
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

// Returns cell's value
double Cell::get_value() const
{
    return value;
}

// Resets the state of a cell
// - clears its value (has to be evaluated again)
void Cell::reset()
{
    if (!evaluable) return;

    on_stack = false;
    error = false;
    error_message = "";
    dirty = true;
    value = 0;
}

// Sets cell's on_cycle flag
void Cell::put_on_cycle()
{
    if (!evaluable) return;
    error = true;
    error_message = CYCERR;
    dirty = false;
    value = 0;
}

// Returns printable content of the cell
// (value, error or "Not evaluated" string)
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

// Returns original text of the cell
const std::string &Cell::get_text() const
{
    return original_text;
}

