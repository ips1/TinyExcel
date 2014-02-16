#include <iostream>

#include "table.h"
#include "postfix.h"
#include "parsing.h"
#include "interactive.h"

// Prints usage of the program
void usage(std::string fname)
{
    std::cout << "Usage:" << std::endl;
    std::cout << fname << " ... interactive mode" << std::endl;
    std::cout << fname << " in out ... evaluates table from file in and stores it to file out" << std::endl;
}

// Non-interactive mode of the program
// Loads a table from input file
// Evaluates the table
// Saves the table to output file
int non_interactive(std::string inf, std::string outf)
{
    Table t;
    try
    {
        t.load(inf);
    }
    catch (FileOpenException &ex)
    {
        std::cout << "File " << inf << " can't be opened!" << std::endl;
        return 1;
    }
    try
    {
        t.evaluate();
    }
    catch (EvaluationException &ex)
    {
        std::cout << "Error while evaluating the table!" << std::endl;
        return 1;
    }
    try
    {
        t.save(outf, false);
    }
    catch (FileOpenException &ex)
    {
        std::cout << "File " << outf << " can't be opened!" << std::endl;
        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{

    // Parsing command line arguments
    std::vector<std::string> args(argv, argv + argc);

    // Return value of main
    int res = 0;

    // No arguments = interactive mode
    if (argc < 2)
    {
        InteractiveContext con;
        con.start_loop(std::cin);
    }
    // Two arguments = non-interactive mode
    else if (argc == 3)
    {
        res = non_interactive(args[1], args[2]);
    }
    // Other number of arguments = usage
    else
    {
        usage(args[0]);
        res = 1;
    }

    return res;

}
