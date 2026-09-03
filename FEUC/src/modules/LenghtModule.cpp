#include "PCH.hpp"
#include "modules/LenghtModule.hpp"
#include "StringUtils.hpp"

LenghtModule::LenghtModule(const std::vector<std::string>& args) : BaseModule(args)
{
	AddUnits(std::unordered_map<std::string, LDouble>({
		{"nm", 1e-9},
		{"µm", 1e-6},
		{"mm", 1e-3},
		{"cm", 1e-2},
		{"dm", 1e-1},
		{"m", 1.0},
		{"dam", 10.0},
		{"hm", 100.0},
		{"km", 1000.0},
		{"ft", 0.3048},
		{"yd", 0.9144},
		{"mi", 1609.344},
		}));
}

LenghtModule::~LenghtModule()
{

}
void LenghtModule::StartConvertUnit()
{
	ParseResult result = StartParseArguments();
	if (result.ParseError)
	{
		std::cerr << "Error parsing arguments.\n";
		return;
	}
	bool convErr;

	LDouble convertedValue = StringUtils::StringToValue<LDouble>(result.Value, convErr);
	if (convErr)
	{
		std::cerr << "Couldn't convert value\n";
		return;
	}

	LDouble finalValue = ConvertLength(convertedValue, result.FromUnit, result.ToUnit);

	short prec = -1;
	if (!result.Precision.empty())
	{
		prec = (short)StringUtils::StringToValue<int>(result.Precision, convErr);
		if (convErr)
		{
			std::cerr << "Couldn't convert precision\n";
			return;
		}
	}

	Output(StringUtils::FormatString("{} {} = {} {}", convertedValue, result.FromUnit, StringUtils::ToString(finalValue, prec), result.ToUnit));
}
LDouble LenghtModule::ConvertLength(LDouble value, const std::string& fromUnit, const std::string& toUnit)
{
	LDouble valueInMeters = ToMeters(value, fromUnit);

	return FromMeters(valueInMeters, toUnit);
}
LDouble LenghtModule::ToMeters(LDouble value, const std::string& fromUnit)
{
	bool err;
	
	LDouble factor = GetUnitFactor(fromUnit, err);
	if (err)
	{
		std::cerr << "Couldn't convert to meters\n";
		return 0.f;
	}
	return value * factor;

}
LDouble LenghtModule::FromMeters(LDouble value, const std::string& toUnit)
{
	bool err;
	LDouble factor = GetUnitFactor(toUnit, err);

	if (err)
	{
		std::cerr << "Couldn't convert to meters\n";
		return 0.f;
	}
	return value / factor;
}