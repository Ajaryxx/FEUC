#pragma once
#include <string>
#include <algorithm>
#include <cmath>
#include <cctype>

class StringUtils
{
public:
	static std::string LowerStr(const std::string& str)
	{
		std::string MStr;
		MStr.reserve(str.size());

		std::transform(str.begin(), 
			str.end(), 
			std::back_inserter(MStr), 
			[](unsigned char c) 
			{ 
				return static_cast<char>(std::tolower(c));
			});

		return MStr;
	}
	static std::string ToUpper(const std::string& str)
	{
		std::string MStr;
		MStr.reserve(str.size());

		std::transform(str.begin(), 
			str.end(), 
			std::back_inserter(MStr), 
			[](unsigned char c) 
			{ 
				return static_cast<char>(std::toupper(c)); 
			});

		return MStr;
	}
	/*-------------ToString Functions-------------T*/
	//String format
	static std::string ToString(const char* str) { return std::string(str); }
	static std::string ToString(const std::string& str) { return str; }

	//Numeric format
	static std::string ToString(int value) { return std::to_string(value); }
	static std::string ToString(long long value) { return std::to_string(value); }

	//Floating point format
	static std::string ToString(float value, short decimalPlaces = -1) 
	{ 
		if (decimalPlaces != -1)
		{
			return PopBackZeros(std::to_string(RoundToDecimalPlaces(value, decimalPlaces)));
		}
		return PopBackZeros(std::to_string(value));
	}
	static std::string ToString(double value, short decimalPlaces = -1) 
	{ 
		if (decimalPlaces != -1)
		{
			return PopBackZeros(std::to_string(RoundToDecimalPlaces(value, decimalPlaces)));
		}
		return PopBackZeros(std::to_string(value));
	}
	static std::string ToString(long double value, short decimalPlaces = -1) 
	{ 
		if (decimalPlaces != -1)
		{
			return PopBackZeros(std::to_string(RoundToDecimalPlaces(value, decimalPlaces)));
		}
		return PopBackZeros(std::to_string(value));
	}

	//Boolean format
	static std::string ToString(bool value) { return value ? "true" : "false"; }
	/*--------------------------------------------T*/


	template<typename... Args>
	static std::string FormatString(const std::string& str, Args... args);

private:
	template<typename T, typename... Args>
	static std::string ParseArguments(const std::string& str, size_t offset, T arg, Args... args);

	static std::string ParseArguments(const std::string& str, size_t offset)
	{
		return str;
	}

	static std::string PopBackZeros(const std::string& str)
	{
		if (str.empty())
			return str;

		std::string result = str;
		size_t i = result.length() - 1;

		while (!result.empty() && result[i--] == '0')
		{
			result.pop_back();
		}
		if (!result.empty() && result.back() == '.')
		{
			result.pop_back();
		}

		return result;
	}

	static long double RoundToDecimalPlaces(long double value, short decimalPlaces)
	{
		long double multiplier = std::pow(10.0L, decimalPlaces);
		return std::round(value * multiplier) / multiplier;
	}

};
template<typename... Args>
std::string StringUtils::FormatString(const std::string& str, Args... args)
{
	return StringUtils::ParseArguments(str, 0, args...);
}

template<typename T, typename... Args>
std::string StringUtils::ParseArguments(const std::string& str, size_t offset, T arg, Args... args)
{
	std::string result = str;
	size_t i = result.find("{}", offset);

	if (i != std::string::npos)
	{
		std::string replacement = ToString(arg);
		result.replace(i, 2, replacement);

		offset = i + replacement.length();
		return ParseArguments(result, offset, args...);
	}
	return result;
}