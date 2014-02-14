#include <iostream>
#include <memory>

#include "table_loader.h"
#include "table.h"
#include "postfix.h"
#include "parsing.h"

int main()
{

    // TODO: FileOpenException
    Table t = load_table("in.txt");
    t.evaluate();
    save_table(t, "out1.txt", false);

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

    save_table(t, "out2.txt", true);

    return 0;

}
