/*********************************************************************
 *	@file		INIFile.cpp
 *	@brief		类INIFile的实现
 *
 *
 *	Date        Name        Description
 *	04/03/15	MYLS		Creation.
 *
 *********************************************************************/

#include <iostream>
#include "INIFile.h"


INIFile::
INIFile() :
	_File()
{}


INIFile::
~INIFile()
{
	if (_File.is_open())
		_File.close();
}

bool INIFile::
openFile(const std::string & filePath)
{
	if (_File.is_open())
		_File.close();
	_Table.clear();
	_File.open(filePath, std::ios::in);

	if (!_File.is_open()) {
		std::cerr << "INIFile::Can not open file (" + filePath + ")!" << std::endl;
		return false;
	}

	std::string line, section;
	while (!_File.eof()) {
		getline(_File, line);
		trim(line);
		if (line.empty())
			continue;

		switch (line.front()) {
		case'[':
			if (line.back() == ']')
				section = line.substr(1, line.length() - 2);
			break;
		case'#':
		case';':
		case' ':
			break;
		default:
			int indexOfEqual = line.find_first_of('=');
			if (std::string::npos == indexOfEqual)
				break;
			std::string key = line.substr(0, indexOfEqual);
			std::string value = line.substr(indexOfEqual + 1);
			_Table[section][std::move(trim(key))] = std::move(trim(value));
			break;
		}
	}

	return true;
}

std::string INIFile::
getString(const std::string & section, const std::string & key) const
{
	if (!_File.is_open()) {
		std::cerr << "INIFile::File Not Open!" << std::endl;
		return "";
	}

	auto theSection = _Table.find(section);
	if (theSection == _Table.end()) {
		std::cerr << "INIFile::No such section(" + section + ")!" << std::endl;
		return "";
	}

	auto theKey = theSection->second.find(key);
	if (theKey == theSection->second.end()) {
		std::cerr << "INIFile::No such key(" + key + ")!" << std::endl;
		return "";
	}

	return theKey->second;
}

void INIFile::
print()
{
	for (auto & map : _Table) {
		std::cout << '[' << map.first << ']' << std::endl;
		for (auto & it : map.second)
			std::cout << it.first << " = " << it.second << std::endl;
	}
}

std::string& INIFile::
trim(std::string & str) const
{
	if (str.empty()) 
		return str;
	
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
	return str;
}

