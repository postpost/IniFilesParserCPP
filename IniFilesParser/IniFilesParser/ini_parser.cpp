#include "ini_parser.h"
#include <fstream>
#include "file_errors.h"
#include <forward_list>

ini_parser::ini_parser(std::string& fileName) : _fileName{ fileName }
{
	
};
//destructor
ini_parser::~ini_parser() {
	_fileIn.close();
}

//remove comments
std::string ini_parser::remove_comments(std::string& str) {
	std::string res;
	bool cmt = false;
	for (int i = 0; i < str.length(); ++i) {
		if (cmt == true && str[i] == '\n')
			cmt = false;
		else if (cmt)
			continue;
		else if (str[i] == ';')
			cmt = true, i++;
		else res += str[i];
	}
	return res;
}

//read_file 
void ini_parser::read_section(std::string section, std::ifstream& fileIn) {
	try {
		fileIn.open(_fileName);
		//read Section
		std::string line;
		if (fileIn.is_open())
		{
			while (!fileIn.eof()) {
				std::getline(fileIn, line);
				//std::cout << line << std::endl;
				if (line[0] == ';' || line.empty()) {
					continue;
				}
				//find Sections
				auto endSectionPos = line.find(']');
				auto curSection = line.substr(endSectionPos - 1);
				//std::cout << curSection.at(0)<< std::endl; 
				sectionNum.resize(count);
				int i = count;
				sectionNum[count++] = curSection.at(0); //store number of section
				char sec_num = curSection.at(0);
				//trim Section
				std::string section;
				std::getline(fileIn, section, '[');
				
				//delete empty spaces
				if (!section.empty()) {
					section.erase(std::remove_if(section.begin(), section.end(),
						[](char c) {
							//Lambda
							return (c == ' ');
						}
					), section.end());
					std::map<std::string, std::string> mss; //to store KeyValue pair
					std::stringstream stream(section);
					std::string chunk;
					while (!stream.eof() && stream >> chunk)
					{
						//remove comments
						chunk = remove_comments(chunk);

						//get key_value pair
						auto delim = chunk.find("=");
						if (delim) {
							auto Key = chunk.substr(0, delim); //iterator
							auto Value = chunk.substr(delim + 1); //iterator
							if (Value.empty())
								continue;
							auto itr = mcm.find(sec_num); // find Section num
							auto itr_2 = mss.find(Key); //find same variable name in mss
							if (itr != mcm.end() && itr_2 != mss.end()) //check if already had this section num
							{
								mss.erase(Value);
								mss.find(Key)->second = Value;
								//mcm.find(sec_num)->first = Value;
								std::cout << mss.find(Key)->second << std::endl;
								continue;
							}
							mss[Key] = Value;
							mcm.insert(std::make_pair(sec_num, mss));
							//std::cout << mss.at(Key);
						}
					}
				}//end of if...!empty()
			} //end of while
		}
	}
	catch(FileError& ex)
	{
		ex.what();
	}

}//end of function

//print map
static void ini_parser::print_map(const auto& mcss)
{
	for (auto it = mcss.begin(); it != mcss.end(); ++it) {
		std::cout << it->first << ":\n";
		for (auto itr = it->second.begin(); itr != it->second.end(); ++itr) {
			std::cout << itr->first << ", " << itr->second << std::endl;
		}

	}
}

//find value in the Section if exists
std::string ini_parser::find_value(std::multimap<char, std::map<std::string, std::string>>& my_map, std::string section_num, std::string key) {
	std::forward_list<std::string> list;
	std::forward_list<std::string> list_2;
	for (auto it = my_map.begin(); it != my_map.end(); it++) {
		if (it->first == section_num[0]) //find section num
		{
			for (auto itr = it->second.begin(); itr != it->second.end(); ++itr) 
			{
				if (itr->first == key) {
					list.push_front(itr->second);
					continue;
				}
				//std::cout << itr->first << ", " << itr->second << std::endl;
				list_2.push_front(itr->first);
			}
		}
	}
	if (!list_2.empty()) {
		list_2.sort();
		list_2.unique();
	}
	if (list.empty() && !list_2.empty()) {
		std::cout << "В данной секции существуют следующие переменные: ";
		for (const auto& el : list_2)
			std::cout << el << ", ";
		return "";
	}
	else {
		std::cout << "Секция пустая\n";
		return "";
	}
	return list.front();
};
