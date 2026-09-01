#include "PCH.hpp"
#include "FEUC.hpp"

#include "modules/HelpModule.hpp"
#include "modules/LenghtModule.hpp"

FEUC::FEUC(const std::vector<std::string>& args)
{
	this->m_args = args;
}
FEUC::~FEUC()
{

}

void FEUC::Run()
{
	std::unique_ptr<BaseModule> module = GetModuleFromCMDL();

	if (module.get())
	{
		module->StartConvertUnit();
	}
	
}
std::unique_ptr<BaseModule> FEUC::GetModuleFromCMDL()
{
	if (m_args.empty())
	{
		std::cerr << "No module specified. Use 'help' for usage information." << std::endl;
		return nullptr;
	}

	std::vector<std::string> moduleArgs(m_args.begin() + 1, m_args.end());

	if (m_args[0] == "help")
	{
		return std::make_unique<HelpModule>(moduleArgs);
	}
	else if (m_args[0] == "length")
	{
		return std::make_unique<LenghtModule>(moduleArgs);
	}
	else
	{
		std::cerr << "Unknown module: [" << m_args[0] << "]. Use 'help' for usage information." << std::endl;
		return nullptr;
	}

	return nullptr;
}
