#include <string>
#include <vector>
#include <iostream>

#include "interactive.h"
#include "exceptions.h"
#include "parsing.h"

// Load command (loads table)
void InteractiveContext::load(const std::string &fname)
{
    try
    {
        t.load(fname);
    }
    catch (FileOpenException &ex)
    {
        std::cerr << "File " << fname << " can't be opened!" << std::endl;
    }
}

// Save command (saves table)
void InteractiveContext::save(const std::string &fname)
{
    try
    {
        t.save(fname, true);
    }
    catch (FileOpenException &ex)
    {
        std::cerr << "File " << fname << " can't be opened!" << std::endl;
    }
}

// Save value command (saves table values)
void InteractiveContext::saveval(const std::string &fname)
{
    try
    {
        t.save(fname, false);
    }
    catch (FileOpenException &ex)
    {
        std::cerr << "File " << fname << " can't be opened!" << std::endl;
    }
}

// Print command (prints current state of entire table)
void InteractiveContext::print()
{
    t.print(std::cout);
}

// Help command
void InteractiveContext::help()
{
    std::cout << std::endl << app_name << " Interactive Mode" << std::endl;
    std::cout << "commands:" << std::endl;
    std::cout << "  load fname ... Loads table" << std::endl;
    std::cout << "  save fname ... Saves table" << std::endl;
    std::cout << "  saveval fname ... Saves values from table" << std::endl;
    std::cout << "  eval ... Evaluates the table" << std::endl;
    std::cout << "  print ... Prints the table content" << std::endl;
    std::cout << "  get cell ... Evaluates cell and prints its value" << std::endl;
    std::cout << "  set cell content ... Sets cell content (resets previously computed values)" << std::endl;
    std::cout << "  help ... Shows this help" << std::endl;
    std::cout << "  about ... About the application" << std::endl << std::endl;
}

// About command
void InteractiveContext::about()
{
    std::cout << std::endl << app_name << " version " << app_version << std::endl;
    std::cout << "(C) " << app_author << " " << app_year << std::endl;
    std::cout << "Special thanks to Vit Sefl for his deep C++ knowledge and advices." << std::endl << std::endl;
}

// Eval command (evaluates entire table)
void InteractiveContext::eval()
{
    try
    {
        t.evaluate();
    }
    catch (EvaluationException &ex)
    {
        std::cerr << "Error while evaluating the table!" << std::endl;
    }
}

// Get command (evaluates cell and prints its value)
void InteractiveContext::getc(const std::string &cell)
{
    try
    {
        CellReference r = coords_to_reference(cell);
        t.evaluate_cell(r);
        Cell &c = t.get_cell(r);
        std::cout << c.get_content() << std::endl;
    }
    catch (InvalidCoordinatesException &ex)
    {
        std::cerr << "Invalid cell coordinates: " << cell << std::endl;
        return;
    }
    catch (CoordinatesOverflowException &ex)
    {
        std::cerr << "Coordinates too large: " << cell << std::endl;
        return;
    }
    catch (EvaluationException &ex)
    {
        std::cerr << "Error while evaluating the cell!" << std::endl;
    }
}

// Set command (sets a content of a cell)
void InteractiveContext::setc(const std::string &cell, const std::string &content)
{
    try
    {
        CellReference r = coords_to_reference(cell);
        t.set_cell(r, content);
        t.reset();
    }
    catch (InvalidCoordinatesException &ex)
    {
        std::cerr << "Invalid cell coordinates: " << cell << std::endl;
        return;
    }
    catch (CoordinatesOverflowException &ex)
    {
        std::cerr << "Coordinates too large: " << cell << std::endl;
        return;
    }
}

// Takes a command, parses it and executes it
// Returns true if the loop should end, false otherwise
bool InteractiveContext::execute_command(const std::string &cmd)
{
    const std::vector<char> delims = {' '};
    std::vector<std::string> parts;

    // Split the command into parts
    parts = split_string(cmd, delims, true, false);

    // Empty command, continue loop
    if (parts.size() == 1 && parts[0] == "") return false;

    // Not empty command, switch by first word, check number of arguments
    if (parts[0] == "load")
    {
        if (parts.size() < 3)
        {
            throw NotEnoughArgumentsException();
        }
        load(parts[2]);
        return false;
    }
    else if (parts[0] == "save")
    {
        if (parts.size() < 3)
        {
            throw NotEnoughArgumentsException();
        }
        save(parts[2]);
        return false;
    }
    else if (parts[0] == "saveval")
    {
        if (parts.size() < 3)
        {
            throw NotEnoughArgumentsException();
        }
        saveval(parts[2]);
        return false;
    }
    else if (parts[0] == "get")
    {
        if (parts.size() < 3)
        {
            throw NotEnoughArgumentsException();
        }
        getc(parts[2]);
        return false;
    }
    else if (parts[0] == "set")
    {
        if (parts.size() < 5)
        {
            throw NotEnoughArgumentsException();
        }
        std::string coords = parts[2];
        parts.erase(parts.begin(), parts.begin() + 4);
        std::string content = merge_string(parts, "");
        trim(content, ' ');
        setc(coords, content);
        return false;
    }
    else if (parts[0] == "print")
    {
        print();
        return false;
    }
    else if (parts[0] == "eval")
    {
        eval();
        return false;
    }
    else if (parts[0] == "help")
    {
        help();
        return false;
    }
    else if (parts[0] == "about")
    {
        about();
        return false;
    }
    else if (parts[0] == "exit")
    {
        // Loop should end, returns true
        return true;
    }
    else
    {
        throw InvalidCommandException();
    }

    return false;
}

// Performs the interactive loop
// - reads user commands, parses it and executes it
void InteractiveContext::start_loop(std::istream &in)
{
    std::string line;
    std::cout << app_name << " " << app_version << " Interactive" << std::endl << std::endl;
    while (!in.eof())
    {
        std::cout << "TinyExcel> ";
        getline(in, line);
        try
        {
            if (execute_command(line)) break;
        }
        catch (InvalidCommandException &ex)
        {
            std::cerr << "Invalid command: " << line << std::endl;
        }
        catch (NotEnoughArgumentsException &ex)
        {
            std::cerr << "Not enough arguments for a command: " << line << std::endl;
        }
    }
}
