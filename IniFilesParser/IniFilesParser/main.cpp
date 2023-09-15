#include <iostream>
#include <fstream>
#include "ini_parser.h"

int main() {
	setlocale(LC_ALL, "ru");
	std::string fileName = "config.ini";
	ini_parser parser(fileName);
	std::string value;
	auto pr = parser.get_value<int>(value);
	std::cout << "Hellooo" << std::endl;
	return 0;
}