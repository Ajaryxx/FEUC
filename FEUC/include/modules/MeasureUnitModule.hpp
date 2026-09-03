#pragma once
#include "modules/BaseModule.hpp"

class MeasureUnitModule : public BaseModule
{
public:
	MeasureUnitModule(const std::vector<std::string>& args);
	~MeasureUnitModule();

private:

	// Inherited via BaseModule
	void StartConvertUnit() override;

	LDouble ConvertLength(LDouble value, const std::string& fromUnit, const std::string& toUnit);

	LDouble ToMeters(LDouble value, const std::string& fromUnit);
	LDouble FromMeters(LDouble value, const std::string& toUnit);

};