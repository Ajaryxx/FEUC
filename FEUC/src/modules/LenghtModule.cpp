#include "PCH.hpp"
#include "modules/LenghtModule.hpp"
#include "StrOperations.hpp"

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

	FormatString("Hallo {} und die Zahl {}", "C++", 5);
}

LenghtModule::~LenghtModule()
{

}
void LenghtModule::Output(const std::string& str)
{
	std::cout << str << std::endl;
}

void LenghtModule::StartConvertUnit()
{
	ParseResult result = ParseArguments(AcceptedUnits);
	if (result.ParseError)
	{
		std::cerr << "Error parsing arguments.\n";
		return;
	}
	bool convErr;

	LDouble convertedValue = ConvertValue<LDouble>(result.Value, convErr);
	if (convErr)
	{
		std::cerr << "Couldn't convert value\n";
		return;
	}

	LDouble finalValue = ConvertLength(convertedValue, result.FromUnit, result.ToUnit);
	
	//std::cout << convertedValue << " " << result.FromUnit << " = " << finalValue << " " << result.ToUnit << std::endl;

}
LDouble LenghtModule::ConvertLength(LDouble value, const std::string& fromUnit, const std::string& toUnit)
{
	LDouble valueInMeters = ToMeters(value, fromUnit);

	return FromMeters(valueInMeters, toUnit);
}
LDouble LenghtModule::ToMeters(LDouble value, const std::string& fromUnit)
{
	auto it = unitConversionFactors.find(fromUnit);
	if (it != unitConversionFactors.end())
	{
		return value * it->second;
	}
	return 0.0f;
}
LDouble LenghtModule::FromMeters(LDouble value, const std::string& toUnit)
{
	auto it = unitConversionFactors.find(toUnit);
	if (it != unitConversionFactors.end())
	{
		return value / it->second;
	}
	return 0.0f;
}
void LenghtModule::AddUnits(const std::unordered_map<std::string, LDouble>& map)
{
	for (const auto& item : map)
	{
		std::string TLString = LowerStr(item.first);
		if (unitConversionFactors.find(TLString) != unitConversionFactors.end())
		{
			assert(false && "Unit already exists.");
		}
		else
		{
			unitConversionFactors[TLString] = item.second;
			AcceptedUnits.push_back(TLString);
		}
		
	}
}