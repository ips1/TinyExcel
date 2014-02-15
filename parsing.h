#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include "exceptions.h"

std::vector<std::string> split_string(const std::string &str, const std::vector<char> &delims, bool include_delims, bool keep_empty);

std::string merge_string(const std::vector<std::string> &parts, const std::string &delim);

void trim(std::string &str, char c);

