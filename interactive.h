#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include <string>
#include <istream>

#include "table.h"

// Global constants regarding the application info
const std::string app_name = "TinyExcel";
const std::string app_version = "1.1";
const std::string app_author = "Petr Kubat";
const std::string app_year = "2014";

// Class for perforimg interaction with the user and it's context
class InteractiveContext
{
private:
    Table t;
    bool execute_command(std::string &cmd);

    // Methods for commands:
    void load(const std::string &fname);
    void save(const std::string &fname);
    void saveval(const std::string &fname);
    void getc(const std::string &cell);
    void setc(const std::string &cell, const std::string &content);
    void eval();
    void help();
    void about();
    void print();

public:
    void start_loop(std::istream &in);
};

#endif // INTERACTIVE_H
