#include <iostream>
#include <memory>
#include "table.h"
#include "postfix.h"
#include "parsing.h"

int main()
{


    Table t;

    t.set_cell(CellReference(1,1),"5");
    t.set_cell(CellReference(2,1),"1");
    t.set_cell(CellReference(1,2),"= (B2) - ( (A1) - (4 * A2 + 3 *A1-1) )");
    t.set_cell(CellReference(3,3),"=(6*1 + 6*1 + 6*1 + 2*1 + 5*1 + 3*1 + 6*1 + 6*3) / 40");
    t.set_cell(CellReference(4,4),"= 3 + A1 * (AHOJ VOLE :D)");
    std::cout << "Done" << std::endl;

    //t.evaluate_cell(CellReference(1,2));
    t.evaluate_cell(CellReference(3,3));
    t.evaluate_cell(CellReference(4,4));
    //t.evaluate_cell(CellReference(80,159));

    std::cout << t.get_cell(CellReference(1,2)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(3,3)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(4,4)).get_content() << std::endl;
    std::cout << t.get_cell(CellReference(80,159)).get_content() << std::endl;


    return 0;

}
