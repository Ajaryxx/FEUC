#pragma once
#include "modules/BaseModule.hpp"

class LenghtModule : public BaseModule
{
public:
	LenghtModule(const std::vector<std::string>& args);
	~LenghtModule();

private:

	// Inherited via BaseModule
	void StartConvertUnit() override;

	LDouble ConvertLength(LDouble value, const std::string& fromUnit, const std::string& toUnit);

	LDouble ToMeters(LDouble value, const std::string& fromUnit);
	LDouble FromMeters(LDouble value, const std::string& toUnit);

};