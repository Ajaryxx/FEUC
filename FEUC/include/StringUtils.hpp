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

	/*-------------StringToValue Functions-------------T*/
	static int StringToInt(const std::string& str, bool& convertError)
	{
		int result = 0;
		try
		{
			size_t offset = 0;
			result = std::stoi(str, &offset);

			if (offset != str.length())
			{
				std::cerr << "Couldn't convert string to int: " << str << std::endl;
				convertError = true;
			}
		}
		catch (const std::invalid_argument& arg)
		{
			std::cerr << arg.what() << std::endl;
			convertError = true;
		}
		catch (const std::out_of_range& arg)
		{
			std::cerr << arg.what() << std::endl;
			convertError = true;
		}

		return result;
	}
	static float StringToFloat(const std::string& str, bool& convertError)
	{
		float result = 0.f;
		try
		{
			size_t offset = 0;
			result = std::stof(str, &offset);

			if (offset != str.length())
			{
				std::cerr << "Couldn't convert string to float: " << str << std::endl;
				convertError = true;
			}
		}
		catch (const std::invalid_argument& arg)
		{
			std::cerr << arg.what() << std::endl;
			convertError = true;
		}
		catch (const std::out_of_range& arg)
		{
			std::cerr << arg.what() << std::endl;
			convertError = true;
		}

		return result;
	}
	static bool StringToBool(const std::string& str, bool& convertError)
	{
		if (str == "true" || str == "1")
			return true;
		else if (str == "false" || str == "0")
			return false;
		else
		{
			std::cerr << "Couldn't convert string to bool: " << str << std::endl;
			convertError = true;
		}
		return false;
	}
	/*--------------------------------------------*/

	template<typename... Args>
	static std::string FormatString(const std::string& str, Args... args);

	template <typename T>
	static T StringToValue(const std::string& str, bool& convertError);

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

template<typename T>
inline T StringUtils::StringToValue(const std::string& str, bool& convertError)
{
	if constexpr (std::is_same_v<T, int>)
	{
		return StringToInt(str, convertError);
	}
	else if constexpr (std::is_same_v<T, float>)
	{
		return StringToFloat(str, convertError);
	}
	else if constexpr (std::is_same_v<T, bool>)
	{
		return StringToBool(str, convertError);
	}
	else
	{
		std::cerr << "Unsupported type for StringToValue conversion." << std::endl;
		convertError = true;
	}

	return T{};
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