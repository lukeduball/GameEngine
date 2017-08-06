#include "StringHelper.h"
#include <iostream>

bool StringHelper::startsWith(std::string fullString, std::string prefix)
{
	if (fullString.substr(0, prefix.length()).find(prefix) != std::string::npos)
	{
		return true;
	}
	return false;
}

bool StringHelper::endsWith(std::string fullString, std::string suffix)
{
	if (fullString.find(suffix, fullString.length() - suffix.length()) != std::string::npos)
	{
		return true;
	}
	return false;
}

std::vector<std::string> StringHelper::split(std::string fullString, std::string delimiter)
{
	std::vector<std::string> vector;
	while (fullString.find(delimiter) != std::string::npos)
	{
		std::string str = fullString;
		str = str.substr(0, fullString.find(delimiter));
		vector.push_back(str);
		fullString = fullString.substr(fullString.find(delimiter) + delimiter.length());
	}
	//Check to see if this is necessary
	if (endsWith(fullString,("\n")))
	{
		fullString = fullString.substr(0, fullString.find_last_of("\n"));
	}
	vector.push_back(fullString);
	return vector;
}