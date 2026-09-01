#include "PCH.hpp"
#include "FEUC.hpp"

#include "modules/HelpModule.hpp"

bool FEUC::m_ErrorState = false;
std::string FEUC::m_ErrString;

FEUC::FEUC(const std::vector<std::string>& args)
{
	this->m_args = args;
}
FEUC::~FEUC()
{

}

void FEUC::Run()
{
	Result result = GetModuleFromCMDL();
	if (result.HasError())
		std::cerr << result.GetErrorMessage() << std::endl;

}
Result FEUC::GetModuleFromCMDL()
{
	Result result {};
	result.module = nullptr;

	if (m_args.size() <= 1)
	{
		result.SetErrorMessage("No arguments found. Use [feuc help] for help.");
		return result;	
	}

	std::transform(m_args.begin(), m_args.end(), m_args.begin(), [&](std::string& str)
		{ std::transform(str.begin(), str.end(), str.begin(), [&](unsigned char c)
			{ return towlower(c); });
	return str; });
	

	if (m_args[1] == "help")
	{
		result.module = std::make_unique<HelpModule>();
		return result;
	}

	
	result.SetErrorMessage("Invalid module name: [" + m_args[1] + "]");
	return result;
			
}
