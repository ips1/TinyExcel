#include <iostream>
#include <memory>
#include "table.h"
#include "postfix.h"
#include "parsing.h"

using namespace std;

int main()
{
    PostfixExpression expr;


    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Value(5)))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Value(1)))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Value(2)))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Addition))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Value(4)))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Multiplication))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Addition))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Value(3)))));
    expr.add_element(PostfixElement(std::move(std::unique_ptr<PostfixAtom>(new Subtraction))));

    std::cout << expr.evaluate() << std::endl;

    std::vector<char> delims = {'+', '-', '*', '/', '(', ')'};
    std::vector<std::string> result = split_string("(aho j zz + 18x + 9*AH84 + ABV + 3.179 + 8.64 * + ++ () + ( 5 + ) ( )) + 35x + 891", delims, true);

    std::cout << result.size() << std::endl;

    for (auto it = result.begin(); it < result.end(); it++)
    {
        trim(*it, ' ');
        std::cout << '"' << *it << '"' << std::endl;
    }

    std::vector<CellReference> dependencies;
    Table t;
    //PostfixExpression expr2 = parse_infix("5+(3   * 8 -9) / 125 * 8 + (35) - (35 * 65 + (42 - 8))", t, dependencies);
    PostfixExpression expr2 = parse_infix("(6*1 + 6*1 + 6*1 + 2*1 + 5*1 + 3*1 + 6*1 + 6*3) / 40", t, dependencies);
    std::cout << expr2.evaluate() << std::endl;



    return 0;







}
