#pragma once

#include <string>
#include <vector>

class StringHelper
{
public:
	static bool startsWith(std::string fullString, std::string prefix);
	static bool endsWith(std::string fullString, std::string suffix);
	static std::vector<std::string> split(std::string fullString, std::string delimiter);
};