#include <vector>

#include "parsing.h"

// Splits the string using specified delimiters
// if include_delims is true, delimiters are also included as strings
std::vector<std::string> split_string(std::string str, std::vector<char> delims, bool include_delims, bool keep_empty)
{
    std::vector<std::string> result;

    unsigned minpos = str.length();
    for (auto it = delims.begin(); it < delims.end(); it++)
    {
        unsigned pos = str.find(*it);
        if ((pos != std::string::npos) && (pos < minpos))
        {
            minpos = pos;
        }
    }

    while (minpos < str.length())
    {
        std::string sub = str.substr(0, minpos);
        if (keep_empty || (sub.length() > 0))
        {
            result.push_back(sub);
        }
        if (include_delims)
        {
            result.push_back(str.substr(minpos, 1));
        }
        str.erase(0, minpos + 1);

        minpos = str.length();
        for (auto it = delims.begin(); it < delims.end(); it++)
        {
            unsigned pos = str.find(*it);
            if ((pos != std::string::npos) && (pos < minpos))
            {
                minpos = pos;
            }
        }
    }

    result.push_back(str);

    return result;
}

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



