#include <iostream>
#include <memory>
#include "table.h"
#include "postfix.h"
#include "parsing.h"

using namespace std;

int main()
{


    Table t;

    t.set_cell(CellReference(1,1),"5");
    t.set_cell(CellReference(2,1),"1");
    t.set_cell(CellReference(1,2),"= (B2) - ( (A1) - (4 * A2 + 3 *A1-1) )");
    t.set_cell(CellReference(3,3),"=(6*1 + 6*1 + 6*1 + 2*1 + 5*1 + 3*1 + 6*1 + 6*3) / 40");
    std::cout << "Done" << std::endl;

    std::cout << t.evaluate_cell(CellReference(1,2)) << std::endl;
    std::cout << t.evaluate_cell(CellReference(3,3)) << std::endl;
    std::cout << t.evaluate_cell(CellReference(80,159)) << std::endl;




    return 0;







}
