#include "PCH.hpp"
#include "modules/DataUnitModule.hpp"
#include "StringUtils.hpp"

DataUnitModule::DataUnitModule(const std::vector<std::string>& args) : BaseModule(args)
{
	AddUnits(std::unordered_map<std::string, LDouble>({
        {"bit",  0.000000125L},
        {"byte", 0.000001L},
        {"kb",   0.001L},
        {"mb",   1.0L},
        {"gb",   1000.0L},
        {"tb",   1e6L},
        {"pb",   1e9L},
        {"eb",   1e12L},
        {"zb",   1e15L},
        {"yb",   1e18L},
        {"rb",   1e21L},
        {"qb",   1e24L}
	}));
}

DataUnitModule::~DataUnitModule()
{

}

void DataUnitModule::StartConvertUnit()
{
	ParseResult result = StartParseArguments();
    if (result.ParseError)
    {
		std::cerr << "Error parsing arguments.\n";
        return;
    }

    bool err;
	LDouble convertedValue = StringUtils::StringToValue<LDouble>(result.Value, err);
    if (err)
    {
		std::cerr << "Error converting value.\n";
        return;
    }

    if(convertedValue != std::floor(convertedValue))
    {
        std::cerr << "Error: Value must be a whole number.\n";
        return;
    }

	const LDouble finalValue = ConvertDataUnit(convertedValue, result.FromUnit, result.ToUnit);

	Output(StringUtils::FormatString("{} {} = {} {}", convertedValue, result.FromUnit, StringUtils::ToString(finalValue, -1), result.ToUnit));
}

LDouble DataUnitModule::ConvertDataUnit(LDouble value, const std::string& fromUnit, const std::string& toUnit)
{
	const LDouble baseValue = FromUnitToBase(value, fromUnit);

    return ToBaseToUnit(baseValue, toUnit);
}

LDouble DataUnitModule::FromUnitToBase(LDouble value, const std::string& fromUnit)
{
	bool err;
    LDouble unitFactor = GetUnitFactor(fromUnit, err);
    if (err)
		return 0.L;

    return value * unitFactor;
}

LDouble DataUnitModule::ToBaseToUnit(LDouble value, const std::string& toUnit)
{
	bool err;
    LDouble unitFactor = GetUnitFactor(toUnit, err);

    if (err)
		return 0.L;

	if (unitFactor == 0)
	{
		std::cerr << "Error: Unit factor for " << toUnit << " is zero, cannot convert." << std::endl;
		return 0.L;
	}

    return value / unitFactor;
}
