#pragma once

class BaseModule
{
public:
	BaseModule() { }
	virtual ~BaseModule() { }

	 

private:
	virtual void Output(const std::string& str) = 0;

};