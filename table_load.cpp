#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "table.h"
#include "parsing.h"
#include "exceptions.h"

// Cell delimiter in a file
const char delim = ';';

// Loads table content from a file
void Table::load(std::string fname)
{
    const std::vector<char> delims = {delim};
    std::ifstream in(fname);
    if (in.fail()) throw FileOpenException();

    // Delete old table
    data.clear();

    int k = 0;

    while (!in.eof())
    {
        k++;
        std::string line;
        // Load a line
        getline(in, line);
        // Split a line by cell delimiter
        std::vector<std::string> parsed = split_string(line, delims, false, true);
        int l = 0;
        for (auto it = parsed.begin(); it < parsed.end(); it++)
        {
            l++;
            // Remove spaces
            trim(*it, ' ');
            // Dont put empty cells
            if (*it == "") continue;
            std::cout << "PART " << k << ", " << l <<": " << *it << std::endl;
            set_cell(CellReference(k, l), *it);
        }
    }
}

// Saves table content to a file
// if original_text is true, saves original content, not evaluated numbers / errors
void Table::save(std::string fname, bool original_text)
{
    std::ofstream out(fname);
    if (out.fail()) throw FileOpenException();
    int k = 1;
    for (auto ita = data.begin(); ita != data.end(); ita++)
    {
        // Printing empty lines (for empty lines of the table)
        while (k < ita->first)
        {
            out << std::endl;
            k++;
        }
        int l = 1;
        for (auto itb = (ita->second).begin(); itb != (ita->second).end(); itb++)
        {
            // Printing delimiters for empty cells
            while (l < itb->first)
            {
                out << delim;
                l++;
            }
            // Printing the cell itself
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

