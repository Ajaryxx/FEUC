#pragma once


class BaseModule
{
public:
	BaseModule(const std::vector<std::string>& args);
	virtual ~BaseModule();


	virtual void StartConvertUnit() = 0;
	 
protected:
	void ParseArguments(const std::vector<std::string>& AcceptedUnits);

private:

	bool ParseArgumentLine(std::string& Value, std::string& ValueUnit, std::string& TargetUnit, std::string& ErrorMessage);
	bool CheckArgumentUnits(const std::vector<std::string>& AcceptedUnits, const std::string& ValueUnit, const std::string& TargetUnit, std::string& ErrorMessage);

	virtual void Output(const std::string& str) = 0;
	std::vector<std::string> m_args;
};