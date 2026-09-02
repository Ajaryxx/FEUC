#include "PCH.hpp"
#include "modules/BaseModule.hpp"
#include "StringUtils.hpp"

//MODULE ARG IGNORED!
BaseModule::BaseModule(const std::vector<std::string>& args)
{
	this->m_args = args;
}

BaseModule::~BaseModule()
{

}

ParseResult BaseModule::ParseArguments(const std::vector<std::string>& AcceptedUnits)
{
	ParseResult result;
	result.ParseError = true;

	if (m_args.size() < 2 || m_args.size() > 3)
	{
		std::cerr << "Invalid argument list. Use: [value] [from_unit] [to_unit]" << std::endl;
		return result;
	}

	std::string Value;
	std::string FromUnit;
	std::string ToUnit;

	std::string errorMessage;

	//We parse the arguments to extract the value, value unit, and target unit
	if (!ParseArgumentLine(Value, FromUnit, ToUnit, errorMessage))
	{
		std::cerr << errorMessage << std::endl;
		return result;
	}

	//We check if the units are valid and accepted
	if (!CheckArguments(AcceptedUnits, Value, FromUnit, ToUnit, errorMessage))
	{
		std::cerr << errorMessage << std::endl;
		return result;
	}
	
	result.Value = Value;
	result.FromUnit = FromUnit;
	result.ToUnit = ToUnit;
	result.ParseError = false;

	return result;

}
bool BaseModule::ParseArgumentLine(std::string& Value, std::string& FromUnit, std::string& ToUnit, std::string& ErrorMessage)
{
	bool GotDecimal = false;

	for (size_t i = 0; i < m_args[0].length(); i++)
	{
		char c = m_args[0][i];

		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			Value += c;
		}
		else if (c == '.' && !GotDecimal)
		{
			Value += c;
			GotDecimal = true;
		}
		else
		{
			FromUnit.append(m_args[0].begin() + i, m_args[0].end());
			break;
		}
	}

	if (FromUnit.empty())
	{
		FromUnit = m_args[1];

		if (m_args.size() > 2)
		{
			ToUnit = m_args[2];
		}
		else
		{
			ErrorMessage = "Target unit must be defined.";
			return false;
		}
	}
	else
	{
		if (m_args.size() > 2)
		{
			ErrorMessage = "Too many arguments. Use: [value] [from_unit] [to_unit]";
			return false;
		}
		ToUnit = m_args[1];
	}

	return true;
}

bool BaseModule::CheckArguments(const std::vector<std::string>& AcceptedUnits, const std::string& Value, const std::string& FromUnit, const std::string& ToUnit, std::string& ErrorMessage)
{
	if (Value.empty())
	{
		ErrorMessage = "Value must be defined.";
		return false;
	}
	if (std::find(AcceptedUnits.begin(), AcceptedUnits.end(), StringUtils::LowerStr(FromUnit)) == AcceptedUnits.end())
	{
		ErrorMessage = "Invalid user unit: [" + FromUnit + "]";
		return false;
	}
	if (std::find(AcceptedUnits.begin(), AcceptedUnits.end(), StringUtils::LowerStr(ToUnit)) == AcceptedUnits.end())
	{
		ErrorMessage = "Invalid target unit: [" + ToUnit + "]";
		return false;
	}

	return true;
}

void BaseModule::Output(const std::string& str)
{
	std::cout << str << std::endl;
}