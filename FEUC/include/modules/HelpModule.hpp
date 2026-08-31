#pragma once
#include "modules/BaseModule.hpp"

class HelpModule : public BaseModule
{
public:
	HelpModule();
	~HelpModule();
	
private:
	virtual void Output(const std::string& str) override;

};