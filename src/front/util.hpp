#pragma once
#include "globals.hpp"

string get_token_str(int token);

string get_file_prefix(string filename);

int get_array_size(const vector<int>& shape);

int get_array_index(const vector<int>& shape, const vector<int>& indexes);

string get_array_item_eeyore(string ee_name, int index);