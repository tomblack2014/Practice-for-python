/*********************************************************************
 *	@file		INIReader.cpp
 *	@brief		Class INIReader的具体实现。
 *
 *
 *	Date        Name        Description
 *	06/03/15	MYLS		Creation.
 *
 *********************************************************************/

#include "INIReader.h"

bool INIReader::
reload(const std::string & filePath = DEFAULT_FILE_PATH)
{
	return _iniFile.openFile(filePath);
}

std::string INIReader::
getString(const std::string & section, const std::string & key)
{
	return _iniFile.getString(section, key);
}

INIReader::
INIReader(const std::string & filePath)
	: _iniFile()
{
	_iniFile.openFile(filePath);
}

INIReader::
~INIReader()
{}

const std::string INIReader::DEFAULT_FILE_PATH = "Config/test.ini";

