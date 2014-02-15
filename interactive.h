#pragma once

#include <string>
#include <istream>

#include "table.h"

class InteractiveContext
{
private:
    Table t;
    bool execute_command(const std::string &cmd);
    // Methods for commands:
    void load(const std::string &fname);
    void save(const std::string &fname);
    void saveval(const std::string &fname);
    void getc(const std::string &cell);
    void setc(const std::string &cell, const std::string &content);
    void eval();
    void help();
    void print();

public:
    void start_loop(std::istream &in);
};
