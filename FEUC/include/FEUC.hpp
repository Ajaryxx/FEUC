#pragma once

class BaseModule;

class FEUC
{
public:
	FEUC(const std::vector<std::string>& args);
	~FEUC();

	void Run();

public:

private:
	std::unique_ptr<BaseModule> GetModuleFromCMDL();
	

private:
	std::vector<std::string> m_args;
	std::unique_ptr<BaseModule> m_module;
};