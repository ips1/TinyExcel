#include <string>
#include <map>
#include <vector>
#include <sstream>

#include "table.h"

// Sets the text content of a cell (replaces the old one with new one)
void Table::set_cell(const CellReference &t, const std::string &content)
{
    auto res = data[t.get_x()].insert(std::pair<int, Cell>(t.get_y(), Cell(content, *this)));
    if (!res.second)
    {
        res.first->second = Cell(content, *this);
    }
}

// Returns reference to specified cell
// - if the cell does not exist, returns reference to empty cell
Cell &Table::get_cell(const CellReference &t)
{
    try
    {
        return data.at(t.get_x()).at(t.get_y());
    }
    catch (std::out_of_range &ex)
    {
        return empty_cell;
    }
}

// Resets all cells to their default (unevaluated) state
void Table::reset()
{
    for (auto ita = data.begin(); ita != data.end(); ita++)
    {
        for (auto itb = (ita->second).begin(); itb != (ita->second).end(); itb++)
        {
            (itb->second).reset();
        }
    }
}

// Evaluates entire table
void Table::evaluate()
{
    for (auto ita = data.begin(); ita != data.end(); ita++)
    {
        for (auto itb = (ita->second).begin(); itb != (ita->second).end(); itb++)
        {
            evaluate_cell(CellReference(ita->first, itb->first));
        }
    }
}

// Evaluates a cell and gets returns its value
// Solves all dependencies along the way
double Table::evaluate_cell(const CellReference &t)
{
    Cell &c = get_cell(t);
    // Cell is already evaluated
    if (!c.is_dirty()) return c.get_value();
    // Have to evaluate the cell
    // - solving dependencies first
    std::stack<CellReference> stack;
    c.put_on_stack();
    stack.push(t);
    try
    {
        while (!stack.empty())
        {
            CellReference current = stack.top();
            Cell &cur_cell = get_cell(current);
            std::vector<CellReference> dependencies = cur_cell.get_dependencies();
            bool ready = true;
            // Iterate through dependencies
            for (auto it = dependencies.begin(); it < dependencies.end(); it++)
            {
                Cell &next = get_cell(*it);
                // Dependency is allready on stack - cycle detected
                if (next.is_on_stack())
                {
                    next.put_on_cycle();
                }
                else if (next.is_dirty())
                {
                    ready = false;
                    next.put_on_stack();
                    stack.push(*it);
                    break;
                }
            }
            if (ready)
            {
                stack.pop();
                cur_cell.remove_from_stack();
                cur_cell.evaluate();
            }
        }
    }
    catch (CycleException &ex)
    {

    }

    return c.get_value();
}

// Prints the table content
void Table::print(std::ostream &out)
{
    int k, l;
    for (auto ita = data.begin(); ita != data.end(); ita++)
    {
        k = ita->first;
        out << "-- " << k << " --" << std::endl;
        for (auto itb = (ita->second).begin(); itb != (ita->second).end(); itb++)
        {
            Cell &cell = itb->second;
            l = itb->first;
            // Conversion of coordinates back to string format
            int letter_count = 'Z' - 'A' + 1;
            std::vector<char> buffer;
            while (l > 0)
            {
                int mod = ((l-1) % letter_count);
                char c = 'A' + mod;
                l = (l - mod) / letter_count;
                buffer.push_back(c);
            }
            std::stringstream ss;
            // Reversing character order
            for (auto it = buffer.rbegin(); it != buffer.rend(); it++)
            {
                ss << (*it);
            }
            ss << k;

            out << "  " << ss.str() << ":" << std::endl;
            out << "  - |" << cell.get_text() << "|" << std::endl;
            out << "  - Value: " << cell.get_content() << std::endl;
        }
    }
}


// Parses reference to a cell from string coordinates
// Coordinates are in form of ABC123 where letters are columns and numbers rows
CellReference coords_to_reference(const std::string &coords)
{
    CellReference ref;
    bool overflow = false;
    char c = 0;
    int n = 0;
    int m = 0;
    const int letter_count = 'Z' - 'A' + 1;
    unsigned i = 0;
    c = coords[i];
    // Rows
    while ((c >= 'A') && (c <= 'Z') && (i < coords.length()))
    {
        int oldn = n;
        n *= letter_count;
        n += c - 'A' + 1;
        if (n < oldn) overflow = true;
        i++;
        if (i < coords.length()) c = coords[i];
    }
    if (n == 0) throw InvalidCoordinatesException();
    if (i == coords.length()) throw InvalidCoordinatesException();
    // Columns
    while ((c >= '0') && (c <= '9') && (i < coords.length()))
    {
        int oldm = m;
        m *= 10;
        m += c - '0';
        if (m < oldm) overflow = true;
        i++;
        if (i < coords.length())
            c = coords[i];
    }
    if (i != coords.length()) throw InvalidCoordinatesException();
    if (overflow) throw CoordinatesOverflowException();
    ref.set_y(n);
    ref.set_x(m);
    return ref;
}


// Creates postfix expression from infix string representation
// If string doesn't represent infix expression, throws InvalidInfixException
PostfixExpression parse_infix(const std::string &infix, Table &parent_table, std::vector<CellReference> &dependencies)
{
    PostfixExpression expr;
    std::stack<char> opstack;

    // Delimiters of infix expression
    std::vector<char> delims = {'+', '-', '*', '/', '~', '(', ')'};

    // Split the expression into atomic parts
    std::vector<std::string> parts = split_string(infix, delims, true, false);

    try
    {
        char c;
        for (auto it = parts.begin(); it < parts.end(); it++)
        {
            // Trim all the spaces around
            trim(*it, ' ');

            if (it->length() == 0) continue;

            if ((*it) == "(")
            {
                opstack.push('(');
            }
            else if ((*it) == ")")
            {
                while (!opstack.empty())
                {
                    c = opstack.top();
                    if (c == '(') break;
                    opstack.pop();
                    expr.add_element(create_operator(c));
                }
                if (opstack.empty())
                {
                    throw InvalidInfixException();
                }
                opstack.pop();
            }
            else if ((*it) == "~")
            {
                while (!opstack.empty())
                {
                    c = opstack.top();
                    if (c != '~') break;
                    opstack.pop();
                    expr.add_element(create_operator(c));
                }
                opstack.push((*it)[0]);
            }
            else if (((*it) == "*") || ((*it) == "/"))
            {
                while (!opstack.empty())
                {
                    c = opstack.top();
                    if ((c != '*') && (c != '/') && (c != '~')) break;
                    opstack.pop();
                    expr.add_element(create_operator(c));
                }
                opstack.push((*it)[0]);
            }
            else if (((*it) == "+") || ((*it) == "-"))
            {
                while (!opstack.empty())
                {
                    c = opstack.top();
                    if (c == '(') break;
                    opstack.pop();
                    expr.add_element(create_operator(c));
                }
                opstack.push((*it)[0]);
            }
            else if ((*it)[0] >= 'A' && (*it)[0] <= 'Z')
            {
                CellReference ref;
                try
                {
                    ref = coords_to_reference(*it);
                }
                catch (InvalidCoordinatesException &ex)
                {
                    throw InvalidInfixException();
                }
                catch (CoordinatesOverflowException &ex)
                {
                    throw InvalidInfixException();
                }
                dependencies.push_back(ref);
                expr.add_element(create_reference(ref, parent_table));
            }
            else
            {
                std::stringstream s(*it);
                double d;
                // Number parsing failed
                if (!(s >> d))
                {
                    throw InvalidInfixException();
                }
                expr.add_element(create_value(d));
            }
        }

        while (!opstack.empty())
        {
            c = opstack.top();
            if (c == '(') break;
            opstack.pop();
            expr.add_element(create_operator(c));
        }

        if (!opstack.empty())
        {
            throw InvalidInfixException();
        }
    }
    catch (InvalidOperatorException &ex)
    {
        throw InvalidInfixException();
    }

    return std::move(expr);
}

// Creates PostfixElement Reference for specified cell
PostfixElement create_reference(CellReference r, Table &parent_table)
{
    return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Reference(r, parent_table))));
}

// -- Reference : PostfixElement --
// Overriding evaluate method
// Evaluation of reference inside the postfix expression - just fetches the value and puts it on stack
 void Reference::evaluate(PostfixStack& current_stack)
{
    double val;
    Cell &c = parent_table.get_cell(target);
    // All dependencies have to be solved in advance
    if (c.is_dirty())
    {
        throw EvaluationException();
    }
    else if (c.has_error())
    {
        throw DependencyException();
    }
    else
    {
        val = c.get_value();
    }
    current_stack.push(val);
}
