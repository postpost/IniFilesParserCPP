#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

class ini_parser {
protected:
	std::string _fileName;
	std::ifstream _fileIn;
	std::string sectionNum;
	int count = 0;
	std::multimap<char, std::map<std::string, std::string>> mcm;
	
public:
	ini_parser(std::string& fileName);
	//destructor
	~ini_parser();

	static std::string remove_comments(std::string& str);

	void read_section(std::string section, std::ifstream& fileIn);
	std::string find_value(std::multimap<char, std::map<std::string, std::string>>& my_map, std::string section_num, std::string key);
	//get_value
	template<class T>
	T get_value (std::string value) {
		//find section num and key
		auto sec_num = value.find('.');
		auto section = value.substr(0, sec_num);
		auto key = value.substr(sec_num+1);

		read_section(value,_fileIn);
		std::string res = find_value(mcm, section, key);
		T res_type{};
		if (res == "")
			return res_type; //как вернуть пустоту?
		std::istringstream convert(res);
		if (convert>>res_type)
			return res_type;
	}

	static void print_map(const auto& mcss);

	
};
