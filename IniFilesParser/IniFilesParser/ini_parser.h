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
public:
	ini_parser(std::string fileName) : _fileName{ fileName } 
	{
		_fileIn.open(_fileName);
	};
	//destructor
	~ini_parser() {
		_fileIn.close();
	}

	//struct to trim section
	template <class T, class U>
	struct Section{
		std::string sectionNum;
		std::multimap<T, U> KeyValue;
		int count = 0; //to count section num
			
		Section(std::string& section) {
			sectionNum = section;
		}

		void read_section(std::string section, std::ifstream& fileIn) {
		//read Section
			std::string line;
			if (fileIn.is_open()) 
			{				
				while (!fileIn.eof()) {
					std::getline(fileIn, line);
					std::cout << line << std::endl;
					if (line[0] == ';' || line.empty()) {
						continue;
					}
					//find Sections
					auto endSectionPos = line.find(']');
					auto curSection = line.substr(endSectionPos - 1);
					//std::cout << curSection.at(0)<< std::endl; 
					sectionNum.resize(count);
					sectionNum[count++] = curSection.at(0); //store number of section
				
				//trim Section
					std::string section;
					std::getline(fileIn, section, '[');
					if (!section.empty()) {
						std::cout << section << std::endl;
						//erase comment
						if (section[0] == ';' || section.find(";"))
						{
							auto findComments = section.find(";");
							auto findEndComments = section.find("\n");
							//erase comments
							section.erase(findComments, findEndComments);
							//std::cout << section_1 << std::endl;
						}
						//find key and value (находит только одно значение)
						auto delim = section.find("=");
						if (delim) {
							auto Key = section.substr(0, delim - 1);
							auto Value = section.substr(delim + 1, ' ' || ';');
							std::cout << Key << '\t' << Value << std::endl;
							//KeyValue.insert(Key, Value);
						}
					}//end of if...!empty()
				} //end of while
			}
		}//end of function
	}; //end of Struct

	//get_value
	template<class T, class U>
	T get_value (U value) {
		//if T == <int> -->
		//iif T == <std::string> -->
		//1. define which section is
		Section <T, U> section (value); //U == KEY; T == VALUE
		section.read_section(value,_fileIn);
		T res = 0;
		return res;
	}

};
