#pragma once

class BaseModule
{
public:
	BaseModule() { }
	virtual ~BaseModule() { }

	virtual void Output(const std::string& str) = 0;

};