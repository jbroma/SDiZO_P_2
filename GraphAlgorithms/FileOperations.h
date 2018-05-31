#pragma once

#include <string>
#include <iostream>
#include <fstream>

void saveToFile(std::string input_data, std::string file_path = "tests.txt");
int* loadFromFile(std::string file_name);

