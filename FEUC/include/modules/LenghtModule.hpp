#pragma once
#include "modules/BaseModule.hpp"

class LenghtModule : public BaseModule
{
public:
	LenghtModule(const std::vector<std::string>& args);
	~LenghtModule();

private:
	virtual void Output(const std::string& str) override;


	// Inherited via BaseModule
	void StartConvertUnit() override;


};