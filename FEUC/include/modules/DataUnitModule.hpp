#pragma once
#include "modules/BaseModule.hpp"

class DataUnitModule : public BaseModule
{
public:
	DataUnitModule(const std::vector<std::string>& args);
	~DataUnitModule();

private:

	// Inherited via BaseModule
	void StartConvertUnit() override;
	
	LDouble ConvertDataUnit(LDouble value, const std::string& fromUnit, const std::string& toUnit);

	LDouble FromUnitToBase(LDouble value, const std::string& fromUnit);
	LDouble ToBaseToUnit(LDouble value, const std::string& toUnit);

};