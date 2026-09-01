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
		std::cerr << "Invalid argument list. 2 or 3 arguments are expected." << std::endl;
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
	if (!CheckArgumentUnits(AcceptedUnits, ValueUnit, TargetUnit, errorMessage))
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
	}
	else
	{
		if (m_args.size() > 2)
		{
			ErrorMessage = "Invalid argument list. 2 or 3 arguments are expected.";
			return false;
		}
		TargetUnit = m_args[1];
	}

	return true;
}

bool BaseModule::CheckArgumentUnits(const std::vector<std::string>& AcceptedUnits, const std::string& ValueUnit, const std::string& TargetUnit, std::string& ErrorMessage)
{
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