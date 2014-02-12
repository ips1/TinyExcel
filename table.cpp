#include "table.h"

void Table::set_cell(const CellReference &t, std::string content)
{
    auto res = data[t.x].insert(std::pair<int, Cell>(t.y, Cell(content, *this)));
    if (res.second == false)
    {
        res.first->second = Cell(content, *this);
    }
}

Cell &Table::get_cell(const CellReference &t)
{
    try
    {
        return data.at(t.x).at(t.y);
    }
    catch (std::out_of_range &ex)
    {
        return empty_cell;
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
                    // TODO - CYCLE DETECTED!!!
                }
                if (next.is_dirty())
                {
                    ready = false;
                    next.put_on_stack();
                    stack.push(*it);
                }
            }
            if (ready == true)
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

// Parses reference to a cell from string coordinates
// Coordinates are in form of ABC123 where letters are columns and numbers rows
CellReference coords_to_reference(std::string coords)
{
    CellReference ref;
    char c = 0;
    int n = 0;
    int m = 0;
    const int letterRange = 'Z' - 'A' + 1;
    int i = 0;
    c = coords[i];
    while ((c >= 'A') && (c <= 'Z') && (i < coords.length()))
    {

        n *= letterRange;
        n += c - 'A' + 1;
        i++;
        if (i < coords.length()) c = coords[i];

    }
    if (n == 0) throw InvalidCoordinatesException();
    if (i == coords.length()) throw InvalidCoordinatesException();
    while ((c >= '0') && (c <= '9') && (i < coords.length()))
    {
        m *= 10;
        m += c - '0';
        i++;
        if (i < coords.length())
            c = coords[i];
    }
    if (i != coords.length()) throw InvalidCoordinatesException();
    // TODO: DELETE THIS
    std::cout << "X: " << m << ", Y: " << n << std::endl;
    ref.y = n;
    ref.x = m;
    return ref;
}


// Creates postfix expression from infix string representation
// If string doesn't represent infix expression, throws InvalidInfixException
PostfixExpression parse_infix(std::string infix, Table &parent_table, std::vector<CellReference> &dependencies)
{
    PostfixExpression expr;
    std::stack<char> opstack;

    // Delimiters of infix expression
    std::vector<char> delims = {'+', '-', '*', '/', '(', ')'};

    // Split the expression into atomic parts
    std::vector<std::string> parts = split_string(infix, delims, true);

    try
    {
        char c;
        for (auto it = parts.begin(); it < parts.end(); it++)
        {
            // Trim all the spaces around
            trim(*it, ' ');

            std::cout << *it << std::endl;

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
            else if (((*it) == "*") || ((*it) == "/"))
            {
                while (!opstack.empty())
                {
                    c = opstack.top();
                    if ((c != '*') && (c != '/')) break;
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
                    std::cout << (*it) << std::endl;
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



PostfixElement create_reference(CellReference ref, Table &parent_table)
{
    return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Reference(ref, parent_table))));
}

// -- Reference : PostfixElement --
// Overriding evaluate method
 void Reference::evaluate(PostfixStack& current_stack)
{
    double val;
    Cell &c = parent_table.get_cell(target);
    // All dependencies have to be solved in advance
    if (c.is_dirty())
    {
        throw EvaluationException();
    }
    else
    {
        val = c.get_value();
    }
    current_stack.push(val);
}
