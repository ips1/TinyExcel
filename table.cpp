#include "table.h"
#include <iostream>

void Reference::evaluate(PostfixStack& current_stack)
{
//    current_stack.push(target.getValue());
}


CellReference coords_to_reference(std::string coords)
{
    CellReference ref;
    ref.x = 0;
    ref.y = 0;
    return ref;
}


// Creates postfix expression from infix string representation
// If string doesn't represent infix expression, throws InvalidInfixException
PostfixExpression parse_infix(std::string infix, const Table &parent_table, std::vector<CellReference> &dependencies)
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
                    opstack.pop();
                    if (c == '(') break;
                    expr.add_element(create_operator(c));
                }
                if (opstack.empty())
                {
                    throw InvalidInfixException();
                }
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
            else if ((*it)[0] > 'A' && (*it)[0] < 'Z')
            {
                CellReference ref = coords_to_reference(*it);
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



PostfixElement create_reference(CellReference ref, const Table &parent_table)
{
    return PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Reference(ref, parent_table))));
}

