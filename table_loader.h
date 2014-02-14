#include <string>

#include "table.h"

Table load_table(std::string fname);
void save_table(Table &t, std::string fname, bool original_text);
