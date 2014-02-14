#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "table.h"
#include "parsing.h"
#include "exceptions.h"

void Table::load(std::string fname)
{
    const std::vector<char> delim = {';'};
    std::ifstream in(fname);
    if (in.fail()) throw FileOpenException();

    data.clear();

    int k = 0;

    while (!in.eof())
    {
        k++;
        std::string line;
        getline(in, line);
        std::vector<std::string> parsed = split_string(line, delim, false, true);
        int l = 0;
        for (auto it = parsed.begin(); it < parsed.end(); it++)
        {
            l++;
            trim(*it, ' ');
            // Dont put empty cells
            if (*it == "") continue;
            std::cout << "PART " << k << ", " << l <<": " << *it << std::endl;
            set_cell(CellReference(k, l), *it);
        }
    }
}


void Table::save(std::string fname, bool original_text)
{

    const char delim = ';';
    std::ofstream out(fname);
    if (out.fail()) throw FileOpenException();
    int k = 1;
    for (auto ita = data.begin(); ita != data.end(); ita++)
    {
        while (k < ita->first)
        {
            out << std::endl;
            k++;
        }
        int l = 1;
        for (auto itb = (ita->second).begin(); itb != (ita->second).end(); itb++)
        {
            while (l < itb->first)
            {
                out << delim;
                l++;
            }
            if (original_text)
            {
                out << (itb->second).get_text();
            }
            else
            {
                out << (itb->second).get_content();
            }
        }
    }

}

