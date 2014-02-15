#include <vector>
#include <string>
#include <sstream>

#include "parsing.h"

// Splits the string using specified delimiters
// if include_delims is true, delimiters are also included as strings
std::vector<std::string> split_string(const std::string &str, const std::vector<char> &delims, bool include_delims, bool keep_empty)
{
    std::vector<std::string> result;
    std::string tmp = str;

    unsigned minpos = tmp.length();
    for (auto it = delims.begin(); it < delims.end(); it++)
    {
        unsigned pos = tmp.find(*it);
        if ((pos != std::string::npos) && (pos < minpos))
        {
            minpos = pos;
        }
    }

    while (minpos < tmp.length())
    {
        std::string sub = tmp.substr(0, minpos);
        if (keep_empty || (sub.length() > 0))
        {
            result.push_back(sub);
        }
        if (include_delims)
        {
            result.push_back(tmp.substr(minpos, 1));
        }
        tmp.erase(0, minpos + 1);

        minpos = tmp.length();
        for (auto it = delims.begin(); it < delims.end(); it++)
        {
            unsigned pos = tmp.find(*it);
            if ((pos != std::string::npos) && (pos < minpos))
            {
                minpos = pos;
            }
        }
    }

    result.push_back(tmp);

    return result;
}

// Merges strings together, with delim between them
std::string merge_string(const std::vector<std::string> &parts, const std::string &delim)
{
    std::stringstream ss;
    bool start = true;
    for (auto it = parts.begin(); it != parts.end(); it++)
    {
        if (start) start = false;
        else ss << delim;
        ss << (*it);
    }
    return ss.str();
}

// Trims occurences of char c at the beginning and at the end
void trim(std::string &str, char c)
{
    int n = 0;
    int len = str.length();
    while ((n < len) && (str[n] == c)) n++;

    str.erase(0, n);

    n = str.length() - 1;
    while ((n >= 0) && (str[n] == c)) n--;
    str.erase(n + 1, str.length() - n - 1);
}



