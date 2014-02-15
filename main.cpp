#include <iostream>
#include <memory>

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
    // Argument
    else if (argc == 3)
    {
        res = non_interactive(args[1], args[2]);
    }
    else
    {
        usage(args[0]);
        res = 1;
    }

    return res;

/*
    Table tt;
    tt.set_cell(CellReference(1,1),"=5+25*(~186)/0.5");
    tt.evaluate();
    std::cout << tt.get_cell(CellReference(1,1)).get_content() << std::endl;


    return 0;

*/

    // TODO: FileOpenException
    Table t;
    t.load("in.txt");
    //t.evaluate_cell(CellReference(2,1));
    t.evaluate();
    //std::cout << std::endl << t.get_cell(CellReference(2,1)).get_content() << std::endl << std::endl;

    t.save("out1.txt", false);

    return 0;
/*
    t.set_cell(CellReference(1,1),"5");
    t.set_cell(CellReference(2,1),"1");
    t.set_cell(CellReference(1,2),"= (B2) - ( (A1) - (4 * A2 + 3 *A1-1) )");
    t.set_cell(CellReference(3,3),"=(6*1 + 6*1 + 6*1 + 2*1 + 5*1 + 3*1 + 6*1 + 6*3) / 40");
    t.set_cell(CellReference(4,4),"= 3 + A1 * (!!!???::: :D)");
    t.set_cell(CellReference(5,5),"= (B2) - ( (A1) - (4 * A2 + 3 *A1-1) + 5 * D4)");
    t.set_cell(CellReference(6,6),"= (B2) - ( (A1) - (4 * A2 + 3 *A1-1) + 5 * E5)");
    t.set_cell(CellReference(7,7),"=A1/A14");

    t.set_cell(CellReference(8,8),"=I9 * 4");
    t.set_cell(CellReference(9,9),"=H8 * 4");
*/

    std::cout << "Done" << std::endl;

    //t.evaluate_cell(CellReference(1,2));
    /*
    t.evaluate_cell(CellReference(3,3));
    t.evaluate_cell(CellReference(4,4));
    t.evaluate_cell(CellReference(5,5));
    t.evaluate_cell(CellReference(6,6));
    t.evaluate_cell(CellReference(7,7));
    t.evaluate_cell(CellReference(8,8));
    */
    //t.evaluate_cell(CellReference(80,159));

    std::cout << "Evaluated" << std::endl;

    std::cout << t.get_cell(CellReference(1,1)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(2,1)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(1,2)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(3,3)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(4,4)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(5,5)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(6,6)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(7,7)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(8,8)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(9,9)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(80,159)).get_content() << std::endl;

    t.save("out2.txt", true);

    return 0;

}
