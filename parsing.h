#ifndef PARSING_H
#define PARSING_H

#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "exceptions.h"

// Additional functions for string operations and parsing

std::vector<std::string> split_string(const std::string &str, const std::vector<char> &delims, bool include_delims, bool keep_empty);

std::string merge_string(const std::vector<std::string> &parts, const std::string &delim);

void trim(std::string &str, char c);

#endif // PARSING_H
