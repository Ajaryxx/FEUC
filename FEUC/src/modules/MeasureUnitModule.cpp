#include "PCH.hpp"
#include "modules/MeasureUnitModule.hpp"
#include "StringUtils.hpp"

MeasureUnitModule::MeasureUnitModule(const std::vector<std::string>& args) : BaseModule(args)
{
	AddUnits(std::unordered_map<std::string, LDouble>({
		{"nm", 1e-9f},
		{"µm", 1e-6f},
		{"mm", 1e-3f},
		{"cm", 1e-2f},
		{"dm", 1e-1f},
		{"m", 1.0f},
		{"dam", 10.0f},
		{"hm", 100.0f},
		{"km", 1000.0f},
		{"ft", 0.3048f},
		{"yd", 0.9144f},
		{"mi", 1609.344f},
		}));
}

MeasureUnitModule::~MeasureUnitModule()
{

}
void MeasureUnitModule::StartConvertUnit()
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
		prec = StringUtils::StringToValue<short>(result.Precision, convErr);
		if (convErr)
		{
			std::cerr << "Couldn't convert precision\n";
			return;
		}
	}

	Output(StringUtils::FormatString("{} {} = {} {}", convertedValue, result.FromUnit, StringUtils::ToString(finalValue, prec), result.ToUnit));
}
LDouble MeasureUnitModule::ConvertLength(LDouble value, const std::string& fromUnit, const std::string& toUnit)
{
	LDouble valueInMeters = ToMeters(value, fromUnit);

	return FromMeters(valueInMeters, toUnit);
}
LDouble MeasureUnitModule::ToMeters(LDouble value, const std::string& fromUnit)
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
LDouble MeasureUnitModule::FromMeters(LDouble value, const std::string& toUnit)
{
	bool err;
	LDouble factor = GetUnitFactor(toUnit, err);
	if (err)
	{
		std::cerr << "Couldn't convert from meters\n";
		return 0.f;
	}
	if (factor == 0.f)
	{
		assert(false && "Factor for unit conversion is zero, which should not happen.");
		return 0.f;
	}
	return value / factor;
}