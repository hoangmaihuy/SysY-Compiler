#pragma once
#include "globals.hpp"

string get_token_str(int token);

string get_file_prefix(string filename);

int get_array_size(const vector<int>& shape);

int get_array_index(const vector<int>& shape, const vector<int>& indexes);

void concat_string_vector(vector<string>& a, const vector<string>& b);

bool name_is_number(const string& name);

bool is_param(const string& name);