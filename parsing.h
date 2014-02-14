#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include "exceptions.h"

//Cell parse_cell(const std::string &str);

std::vector<std::string> split_string(std::string str, std::vector<char> delims, bool include_delims, bool keep_empty);

void trim(std::string &str, char c);

