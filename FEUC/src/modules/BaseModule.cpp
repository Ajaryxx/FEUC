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

ParseResult BaseModule::StartParseArguments()
{
	ParseResult result;
	result.ParseError = true;

	if (m_args.size() < 2 || m_args.size() > 3)
	{
		std::cerr << "Invalid argument list. Use: [Value_And_Unit] [to_unit] [(Optional)Precision]" << std::endl;
		return result;
	}

	std::string Value;
	std::string FromUnit;
	std::string ToUnit;
	std::string Precision;

	std::string errorMessage;

	//We parse the arguments to extract the value, value unit, and target unit
	if (!ParseArgumentLine(Value, FromUnit, ToUnit, Precision, errorMessage))
	{
		std::cerr << errorMessage << std::endl;
		return result;
	}

	//We check if the units are valid and accepted
	if (!CheckArguments(Value, FromUnit, ToUnit, errorMessage))
	{
		std::cerr << errorMessage << std::endl;
		return result;
	}
	
	result.Value = Value;
	result.FromUnit = FromUnit;
	result.ToUnit = ToUnit;
	result.Precision = Precision;
	result.ParseError = false;

	return result;

}
bool BaseModule::ParseArgumentLine(std::string& Value, std::string& FromUnit, std::string& ToUnit, std::string& Precision, std::string& ErrorMessage)
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

	ToUnit = m_args[1];
	if(m_args.size() > 2)
	{
		Precision = m_args[2];
	}

	return true;
}

bool BaseModule::CheckArguments(const std::string& Value, const std::string& FromUnit, const std::string& ToUnit, std::string& ErrorMessage)
{
	if (Value.empty())
	{
		ErrorMessage = "Value must be defined.";
		return false;
	}
	if (std::find(AcceptedUnits.begin(), AcceptedUnits.end(), StringUtils::LowerStr(FromUnit)) == AcceptedUnits.end())
	{
		if (FromUnit.empty())
			ErrorMessage = "Value unit must be defined.";
		else
			ErrorMessage = "Invalid user unit: [" + FromUnit + "]";

		return false;
	}
	if (std::find(AcceptedUnits.begin(), AcceptedUnits.end(), StringUtils::LowerStr(ToUnit)) == AcceptedUnits.end())
	{
		if (ToUnit.empty())
			ErrorMessage = "Target unit must be defined.";
		else
			ErrorMessage = "Invalid target unit: [" + ToUnit + "]";

		return false;
	}

	return true;
}

void BaseModule::Output(const std::string& str)
{
	std::cout << str << std::endl;
}
void BaseModule::AddUnits(const std::unordered_map<std::string, LDouble>& map)
{
	for (const auto& item : map)
	{
		std::string TLString = StringUtils::LowerStr(item.first);
		if (unitConversionFactors.find(TLString) != unitConversionFactors.end())
		{
			assert(false && StringUtils::FormatString("Unit already exists: {}", TLString).c_str());
		}
		else
		{
			assert(item.second > 0 && StringUtils::FormatString("Unit conversion factor must be greater than zero: {} = {}", TLString, item.second).c_str());

			unitConversionFactors[TLString] = item.second;
			AcceptedUnits.push_back(TLString);
		}

	}
}
LDouble BaseModule::GetUnitFactor(const std::string& unit, bool& err) const
{
	auto it = unitConversionFactors.find(StringUtils::LowerStr(unit));
	if (it != unitConversionFactors.end())
	{
		err = false;
		return it->second;
	}
	else
	{
		std::cerr << StringUtils::FormatString("Couldn't find unit: [{}]", unit);
		err = true;
	}
	return 0.f;
}