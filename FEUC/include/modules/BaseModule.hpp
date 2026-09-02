#pragma once


using LDouble = long double;
using LLong = long long;

struct ParseResult
{
	std::string Value;
	std::string FromUnit;
	std::string ToUnit;

	bool ParseError;
};

class BaseModule
{
public:
	BaseModule(const std::vector<std::string>& args);
	virtual ~BaseModule();


	virtual void StartConvertUnit() = 0;
	 
protected:
	ParseResult ParseArguments(const std::vector<std::string>& AcceptedUnits);

	template<typename T>
	T ConvertValue(const std::string& value, bool& convertError);


private:

	bool ParseArgumentLine(std::string& Value, std::string& FromUnit, std::string& ToUnit, std::string& ErrorMessage);
	bool CheckArguments(const std::vector<std::string>& AcceptedUnits, const std::string& Value, const std::string& FromUnit, const std::string& ToUnit, std::string& ErrorMessage);

	virtual void Output(const std::string& str) = 0;
	std::vector<std::string> m_args;
};
template<>
inline LDouble BaseModule::ConvertValue<LDouble>(const std::string& value, bool& convertError)
{
	convertError = false;
	try
	{
		return std::stold(value);
	}
	catch (const std::invalid_argument& arg)
	{
		std::cerr << arg.what() << std::endl;
	}
	catch (const std::out_of_range& arg)
	{
		std::cerr << arg.what() << std::endl;
	}

	convertError = true;
	return LDouble();
}
template<>
inline LLong BaseModule::ConvertValue<LLong>(const std::string& value, bool& convertError)
{
	convertError = false;
	try
	{
		return std::stoll(value);
	}
	catch (const std::invalid_argument& arg)
	{
		std::cerr << arg.what() << std::endl;
	}
	catch (const std::out_of_range& arg)
	{
		std::cerr << arg.what() << std::endl;
	}

	convertError = true;
	return LLong();
}
template<typename T>
inline T BaseModule::ConvertValue(const std::string& value, bool& convertError)
{
	assert(false && "Convert only LLong and LDouble.");

	convertError = true;

	return T();
}