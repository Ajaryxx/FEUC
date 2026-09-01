#include "PCH.hpp"
#include "modules/BaseModule.hpp"

//MODULE ARG IGNORED!
BaseModule::BaseModule(const std::vector<std::string>& args)
{
	this->m_args = args;
}

BaseModule::~BaseModule()
{

}

void BaseModule::ParseArguments(const std::vector<std::string>& AcceptedUnits)
{
	if (m_args.size() < 2 || m_args.size() > 3)
	{
		std::cerr << "Invalid argument list. Use: [value] [from_unit] [to_unit]" << std::endl;
		return;
	}

	std::string Value;
	std::string ValueUnit;
	std::string TargetUnit;

	std::string errorMessage;

	//We parse the arguments to extract the value, value unit, and target unit
	if (!ParseArgumentLine(Value, ValueUnit, TargetUnit, errorMessage))
	{
		std::cerr << errorMessage << std::endl;
		return;
	}

	//We check if the units are valid and accepted
	if (!CheckArguments(AcceptedUnits, Value, ValueUnit, TargetUnit, errorMessage))
	{
		std::cerr << errorMessage << std::endl;
		return;
	}
	
}
bool BaseModule::ParseArgumentLine(std::string& Value, std::string& ValueUnit, std::string& TargetUnit, std::string& ErrorMessage)
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
			ValueUnit.append(m_args[0].begin() + i, m_args[0].end());
			break;
		}
	}

	if (ValueUnit.empty())
	{
		ValueUnit = m_args[1];

		if (m_args.size() > 2)
		{
			TargetUnit = m_args[2];
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
		TargetUnit = m_args[1];
	}

	return true;
}

bool BaseModule::CheckArguments(const std::vector<std::string>& AcceptedUnits, const std::string& Value, const std::string& ValueUnit, const std::string& TargetUnit, std::string& ErrorMessage)
{
	if (Value.empty())
	{
		ErrorMessage = "Value must be defined.";
		return false;
	}
	if (std::find(AcceptedUnits.begin(), AcceptedUnits.end(), ValueUnit) == AcceptedUnits.end())
	{
		ErrorMessage = "Invalid user unit: [" + ValueUnit + "]";
		return false;
	}
	if (std::find(AcceptedUnits.begin(), AcceptedUnits.end(), TargetUnit) == AcceptedUnits.end())
	{
		ErrorMessage = "Invalid target unit: [" + TargetUnit + "]";
		return false;
	}

	return true;
}