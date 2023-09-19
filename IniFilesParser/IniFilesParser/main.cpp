#include <iostream>
#include <fstream>
#include "ini_parser.h"
#include "file_errors.h"


int main() {
	setlocale(LC_ALL, "ru");
	std::string fileName = "config.ini";
	ini_parser parser(fileName);
	std::string value = "4.var3";
	auto pr = parser.get_value<std::string>(value);
	std::cout << pr << std::endl;
	return 0;
}