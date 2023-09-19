#pragma once
#include <iostream>

class FileError:public::std::runtime_error {
public:
	const char* what() const override {
		return "File is not found!\n";
	}
};
