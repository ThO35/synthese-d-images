#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

extern unsigned char minVal;
extern int length, width;
extern std::vector<char> donnes;
extern double scaling;

void read_file();
void read_comments(std::ifstream &file, std::string &str);