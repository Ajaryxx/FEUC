#include "PCH.hpp"
#include "FEUC.hpp"
#include "StringUtils.hpp"

#include "modules/HelpModule.hpp"
#include "modules/MeasureUnitModule.hpp"
#include "modules/DataUnitModule.hpp"

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
	std::string moduleName = StringUtils::LowerStr(m_args[0]);

	if (moduleName == "help")
	{
		return std::make_unique<HelpModule>(moduleArgs);
	}
	else if (moduleName == "length")
	{
		return std::make_unique<MeasureUnitModule>(moduleArgs);
	}
	else if (moduleName == "data")
	{
		return std::make_unique<DataUnitModule>(moduleArgs);
	}
	else
	{
		std::cerr << StringUtils::FormatString("Unknown module: [{}]. Use 'help' for usage information.", moduleName) << std::endl;
	}

	return nullptr;
}
