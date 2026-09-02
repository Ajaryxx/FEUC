#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>

inline std::string LowerStr(const std::string& str)
{
	std::string MStr;
	std::transform(str.begin(), str.end(), std::back_inserter(MStr), [&](char c) { return tolower(static_cast<unsigned int>(c)); });
	return MStr;
}
inline std::string ToUpper(const std::string& str)
{
	std::string MStr;
	std::transform(str.begin(), str.end(), std::back_inserter(MStr), [&](char c) { return toupper(static_cast<unsigned int>(c)); });
	return MStr;
}
template<typename... Args>
inline std::string FormatString(const std::string& str, Args... args)
{
	std::string out;

	std::cout << args << std::endl;

	return out;
}