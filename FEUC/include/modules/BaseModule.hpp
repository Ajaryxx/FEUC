#pragma once

using LDouble = long double;
using LLong = long long;

struct ParseResult
{
	std::string Value;
	std::string FromUnit;
	std::string ToUnit;
	std::string Precision;

	bool ParseError = false;
};

class BaseModule
{
public:
	BaseModule(const std::vector<std::string>& args);
	virtual ~BaseModule();


	virtual void StartConvertUnit() = 0;
	 
protected:
	ParseResult StartParseArguments();
	virtual void Output(const std::string& str);
	void AddUnits(const std::unordered_map<std::string, LDouble>& map);
	LDouble GetUnitFactor(const std::string& unit, bool& err) const;

private:
	bool ParseArgumentLine(std::string& Value, std::string& FromUnit, std::string& ToUnit, std::string& Precision, std::string& ErrorMessage);
	bool CheckArguments(const std::string& Value, const std::string& FromUnit, const std::string& ToUnit, std::string& ErrorMessage);

	std::vector<std::string> m_args;

	std::unordered_map<std::string, LDouble> unitConversionFactors;
	std::vector<std::string> AcceptedUnits;


};
